#ifndef EIGHTIES_IMAGE_IMPL_HPP
#define EIGHTIES_IMAGE_IMPL_HPP

/* =======================================================================
 * image_impl.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/image.hpp"

#include <QImage>

#include <string>

namespace eighties {

class image_impl
{
public:
    explicit image_impl(std::string const& file_name);
    image_impl(image_impl const&) = delete;
    image_impl& operator=(image_impl const&) = delete;
    ~image_impl() noexcept = default;

    QImage const& get_image() const;

private:
    friend class image;
    QImage m_image;
};

inline image_impl* get_impl(image const& im)
{
    return im.m_impl.get();
}

}

#endif
