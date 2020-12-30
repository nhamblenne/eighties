/* =======================================================================
 * image.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/image.hpp"
#include "image_impl.hpp"

namespace eighties {

image::image(image&&) noexcept = default;
image& image::operator=(image&&) noexcept = default;
image::~image() = default;

image::image(std::string const& file_name)
    : m_impl(std::make_unique<image_impl>(file_name))
{
}

image_impl::image_impl(const std::string& file_name)
    : m_image(file_name.c_str())
{
}

image_impl::image_impl(QImage&& im)
    : m_image(std::move(im))
{
}

image::image(std::unique_ptr<image_impl>&& impl) noexcept
    : m_impl(std::move(impl))
{
}

int image::width() const
{
    return m_impl->get_image().width();
}

int image::height() const
{
    return m_impl->get_image().height();
}

QImage const& image_impl::get_image() const
{
    return m_image;
}

image image_impl::create_image()
{
    return image(std::unique_ptr<image_impl>());
}

image image_impl::create_image(QImage&& im)
{
    return image(std::make_unique<image_impl>(std::move(im)));
}


}