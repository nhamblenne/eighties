/* =======================================================================
 * canvas.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "canvas.hpp"

#include "eighties/color.hpp"
#include "eighties/point.hpp"

#include "image_impl.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QWindow>

namespace {

inline QColor toQColor(eighties::color col)
{
    return QColor(col.r, col.g, col.b, col.a);
}

inline uint16_t fromQButton(Qt::MouseButton button)
{
    switch (button) {
        case Qt::LeftButton: return 1;
        case Qt::RightButton: return 2;
        case Qt::MiddleButton: return 3;
        case Qt::ExtraButton1: return 8;
        case Qt::ExtraButton2: return 9;
        default: return 0;
    }
}

inline uint16_t fromQButtons(Qt::MouseButtons buttons)
{
    uint16_t result = 0;
    if (buttons.testFlag(Qt::LeftButton))
        result |= 0x001;
    if (buttons.testFlag(Qt::RightButton))
        result |= 0x002;
    if (buttons.testFlag(Qt::MiddleButton))
        result |= 0x004;
    if (buttons.testFlag(Qt::ExtraButton1))
        result |= 0x080;
    if (buttons.testFlag(Qt::ExtraButton2))
        result |= 0x100;
    return result;
}

inline uint16_t fromAngleDelta(QPoint point)
{
    if (point.y() > 0) return 4;
    if (point.y() < 0) return 5;
    if (point.x() > 0) return 6;
    if (point.x() < 0) return 7;
    return 0;
}

inline eighties::modifiers_t fromQModifiers(Qt::KeyboardModifiers modifiers)
{
    eighties::modifiers_t result = eighties::modifiers_t::none;
    if (modifiers.testFlag(Qt::ShiftModifier))
        result |= eighties::modifiers_t::shift;
    if (modifiers.testFlag(Qt::ControlModifier))
        result |= eighties::modifiers_t::control;
    if (modifiers.testFlag(Qt::AltModifier))
        result |= eighties::modifiers_t::alt;
    if (modifiers.testFlag(Qt::MetaModifier))
        result |= eighties::modifiers_t::meta;
    return result;
}

inline eighties::key_t fromQKey(int key)
{
    switch (key) {
        case Qt::Key_Space: return eighties::key_t::space;
        case Qt::Key_Exclam: return eighties::key_t::exclamation;
        case Qt::Key_QuoteDbl: return eighties::key_t::quotation;
        case Qt::Key_NumberSign: return eighties::key_t::number;
        case Qt::Key_Dollar: return eighties::key_t::dollar;
        case Qt::Key_Percent: return eighties::key_t::percent;
        case Qt::Key_Ampersand: return eighties::key_t::ampersand;
        case Qt::Key_Apostrophe: return eighties::key_t::apostrophe;
        case Qt::Key_ParenLeft: return eighties::key_t::left_parenthesis;
        case Qt::Key_ParenRight: return eighties::key_t::right_parenthesis;
        case Qt::Key_Asterisk: return eighties::key_t::asterisk;
        case Qt::Key_Plus: return eighties::key_t::plus;
        case Qt::Key_Comma: return eighties::key_t::comma;
        case Qt::Key_Minus: return eighties::key_t::minus;
        case Qt::Key_Period: return eighties::key_t::period;
        case Qt::Key_Slash: return eighties::key_t::slash;

        case Qt::Key_0: return eighties::key_t::digit_0;
        case Qt::Key_1: return eighties::key_t::digit_1;
        case Qt::Key_2: return eighties::key_t::digit_2;
        case Qt::Key_3: return eighties::key_t::digit_3;
        case Qt::Key_4: return eighties::key_t::digit_4;
        case Qt::Key_5: return eighties::key_t::digit_5;
        case Qt::Key_6: return eighties::key_t::digit_6;
        case Qt::Key_7: return eighties::key_t::digit_7;
        case Qt::Key_8: return eighties::key_t::digit_8;
        case Qt::Key_9: return eighties::key_t::digit_9;

        case Qt::Key_Colon: return eighties::key_t::colon;
        case Qt::Key_Semicolon: return eighties::key_t::semicolon;
        case Qt::Key_Less: return eighties::key_t::less;
        case Qt::Key_Equal: return eighties::key_t::equal;
        case Qt::Key_Greater: return eighties::key_t::greater;
        case Qt::Key_Question: return eighties::key_t::question;
        case Qt::Key_At: return eighties::key_t::at;

        case Qt::Key_A: return eighties::key_t::a;
        case Qt::Key_B: return eighties::key_t::b;
        case Qt::Key_C: return eighties::key_t::c;
        case Qt::Key_D: return eighties::key_t::d;
        case Qt::Key_E: return eighties::key_t::e;
        case Qt::Key_F: return eighties::key_t::f;
        case Qt::Key_G: return eighties::key_t::g;
        case Qt::Key_H: return eighties::key_t::h;
        case Qt::Key_I: return eighties::key_t::i;
        case Qt::Key_J: return eighties::key_t::j;
        case Qt::Key_K: return eighties::key_t::k;
        case Qt::Key_L: return eighties::key_t::l;
        case Qt::Key_M: return eighties::key_t::m;
        case Qt::Key_N: return eighties::key_t::n;
        case Qt::Key_O: return eighties::key_t::o;
        case Qt::Key_P: return eighties::key_t::p;
        case Qt::Key_Q: return eighties::key_t::q;
        case Qt::Key_R: return eighties::key_t::r;
        case Qt::Key_S: return eighties::key_t::s;
        case Qt::Key_T: return eighties::key_t::t;
        case Qt::Key_U: return eighties::key_t::u;
        case Qt::Key_V: return eighties::key_t::v;
        case Qt::Key_W: return eighties::key_t::w;
        case Qt::Key_X: return eighties::key_t::x;
        case Qt::Key_Y: return eighties::key_t::y;
        case Qt::Key_Z: return eighties::key_t::z;

        case Qt::Key_BracketLeft: return eighties::key_t::left_bracket;
        case Qt::Key_Backslash: return eighties::key_t::backslash;
        case Qt::Key_BracketRight: return eighties::key_t::right_bracket;
        case Qt::Key_AsciiCircum: return eighties::key_t::circumflex;
        case Qt::Key_Underscore: return eighties::key_t::underscore;
        case Qt::Key_QuoteLeft: return eighties::key_t::back_quote;
        case Qt::Key_BraceLeft: return eighties::key_t::left_brace;
        case Qt::Key_Bar: return eighties::key_t::bar;
        case Qt::Key_BraceRight: return eighties::key_t::right_brace;
        case Qt::Key_AsciiTilde: return eighties::key_t::tilde;

        case Qt::Key_Escape: return eighties::key_t::escape;
        case Qt::Key_Tab: return eighties::key_t::tab;
        case Qt::Key_Backspace: return eighties::key_t::backspace;
        case Qt::Key_Enter: return eighties::key_t::enter;
        case Qt::Key_Insert: return eighties::key_t::insert;
        case Qt::Key_Delete: return eighties::key_t::del;
        case Qt::Key_Home: return eighties::key_t::home;
        case Qt::Key_End: return eighties::key_t::end;

        case Qt::Key_Left: return eighties::key_t::left;
        case Qt::Key_Up: return eighties::key_t::up;
        case Qt::Key_Right: return eighties::key_t::right;
        case Qt::Key_Down: return eighties::key_t::down;
        case Qt::Key_PageUp: return eighties::key_t::page_up;
        case Qt::Key_PageDown: return eighties::key_t::page_down;

        case Qt::Key_F1: return eighties::key_t::f1;
        case Qt::Key_F2: return eighties::key_t::f2;
        case Qt::Key_F3: return eighties::key_t::f3;
        case Qt::Key_F4: return eighties::key_t::f4;
        case Qt::Key_F5: return eighties::key_t::f5;
        case Qt::Key_F6: return eighties::key_t::f6;
        case Qt::Key_F7: return eighties::key_t::f7;
        case Qt::Key_F8: return eighties::key_t::f8;
        case Qt::Key_F9: return eighties::key_t::f9;
        case Qt::Key_F10: return eighties::key_t::f10;
        case Qt::Key_F11: return eighties::key_t::f11;
        case Qt::Key_F12: return eighties::key_t::f12;
        case Qt::Key_F13: return eighties::key_t::f13;
        case Qt::Key_F14: return eighties::key_t::f14;
        case Qt::Key_F15: return eighties::key_t::f15;
        case Qt::Key_F16: return eighties::key_t::f16;
        case Qt::Key_F17: return eighties::key_t::f17;
        case Qt::Key_F18: return eighties::key_t::f18;
        case Qt::Key_F19: return eighties::key_t::f19;
        case Qt::Key_F20: return eighties::key_t::f20;
        case Qt::Key_F21: return eighties::key_t::f21;
        case Qt::Key_F22: return eighties::key_t::f22;
        case Qt::Key_F23: return eighties::key_t::f23;
        case Qt::Key_F24: return eighties::key_t::f24;
        case Qt::Key_F25: return eighties::key_t::f25;
        case Qt::Key_F26: return eighties::key_t::f26;
        case Qt::Key_F27: return eighties::key_t::f27;
        case Qt::Key_F28: return eighties::key_t::f28;
        case Qt::Key_F29: return eighties::key_t::f29;
        case Qt::Key_F30: return eighties::key_t::f30;
        case Qt::Key_F31: return eighties::key_t::f31;
        case Qt::Key_F32: return eighties::key_t::f32;

        default: return eighties::key_t::unknown;
    }
}

}

namespace eighties {

canvas::canvas(QWidget* parent, int width, int height)
    : QWidget(parent),
      m_content(width, height, QImage::Format_RGB32)
{
    setAttribute(Qt::WA_InputMethodEnabled);
    setFocusPolicy(Qt::StrongFocus);
    setBackgroundRole(QPalette::Background);
    resize(width, height);
    m_content.fill(QColor(255, 255, 255));
}

void canvas::do_clear()
{
    m_content.fill(QColor(255, 255, 255));
    update();
}

void canvas::do_draw_circle(int xc, int yc, int r, color col)
{
    QPainter painter(&m_content);
    painter.setPen(toQColor(col));
    painter.drawEllipse(QPoint(xc, yc), r, r);
    update(xc-r, yc-r, 2*r, 2*r);
}

void canvas::do_draw_line(int xb, int yb, int xe, int ye, color col)
{
    QPainter painter(&m_content);
    painter.setPen(toQColor(col));
    painter.drawLine(xb, yb, xe, ye);
    update(xb, yb, xe-xb+1, ye-yb+1);
}

void canvas::do_draw_point(int x, int y, color col)
{
    QPainter painter(&m_content);
    painter.setPen(toQColor(col));
    painter.drawPoint(x, y);
    update(x, y, 1, 1);
}

void canvas::do_draw_image(int x, int y, image const& im)
{
    QPainter painter(&m_content);
    auto image_size = get_impl(im)->get_image().size();
    painter.drawImage(QPoint(x, y), get_impl(im)->get_image(),
                      QRect(QPoint(0, 0), image_size));
    update(QRect(QPoint(x, y), image_size));
}

point canvas::do_current_cursor_position() const
{
    QWindow* win = window()->windowHandle();
    if (win == nullptr) {
        return { -1, -1 };
    }
    QScreen* scr = win->screen();
    if (scr == nullptr) {
        return { -1, -1 };
    }
    QPoint pos = QCursor::pos(scr);
    pos = mapFromGlobal(pos);
    return { pos.x(), pos.y() };
}

eighties::event canvas::do_get_event(bool wait)
{
    std::unique_lock guard(m_guard);
    if (wait) {
        m_cond.wait(guard, [this]{ return !m_events.empty(); });
    }
    if (m_events.empty()) {
        return eighties::event{};
    } else {
        auto result = m_events.front();
        m_events.pop_front();
        return result;
    }
}

void canvas::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, m_content, dirtyRect);
}

void canvas::resizeEvent(QResizeEvent* event)
{
    QImage newImage(size(), QImage::Format_RGB32);
    newImage.fill(QColor(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), m_content);
    m_content = newImage;
    QWidget::resizeEvent(event);
    update();
}

QVariant canvas::inputMethodQuery(Qt::InputMethodQuery query) const
{
    return query == Qt::ImFont ? font() : QVariant{};
}

void canvas::inputMethodEvent(QInputMethodEvent* event)
{
    if (!event->commitString().isEmpty()) {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_unknown, Qt::NoModifier, event->commitString());
        keyPressEvent(&keyEvent);
    }
    event->accept();
}

void canvas::keyPressEvent(QKeyEvent* event)
{
    std::unique_lock guard(m_guard);
    m_events.emplace_back(event_type::key_down,
                          key_event{fromQModifiers(event->modifiers()),
                                    fromQKey(event->key()),
                                    static_cast<uint16_t>(event->nativeVirtualKey())});
    m_cond.notify_one();
}

void canvas::mousePressEvent(QMouseEvent* event)
{
    std::unique_lock guard(m_guard);
    m_events.emplace_back(event_type::button_down,
                          button_event{fromQModifiers(event->modifiers()),
                                       fromQButton(event->button()),
                                       fromQButtons(event->buttons()),
                                       event->x(), event->y()});
    m_cond.notify_one();
}

void canvas::mouseReleaseEvent(QMouseEvent* event)
{
    std::unique_lock guard(m_guard);
    m_events.emplace_back(event_type::button_up,
                          button_event{fromQModifiers(event->modifiers()),
                                       fromQButton(event->button()),
                                       fromQButtons(event->buttons()),
                                       event->x(), event->y()});
    m_cond.notify_one();
}

void canvas::wheelEvent(QWheelEvent* event)
{
    std::unique_lock guard(m_guard);
    m_events.emplace_back(event_type::button_wheel,
                          button_event{fromQModifiers(event->modifiers()),
                                       fromAngleDelta(event->angleDelta()),
                                       fromQButtons(event->buttons()),
                                       event->x(), event->y()});
    m_cond.notify_one();
}

}