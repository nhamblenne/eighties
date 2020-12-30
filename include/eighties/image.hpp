#ifndef EIGHTIES_IMAGE_HPP
#define EIGHTIES_IMAGE_HPP

/* =======================================================================
 * image.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <memory>
#include <string>

namespace eighties {

class image_impl;

class image 
{
public:
    explicit image(std::string const& file_name);
    image(image&&) noexcept;
    image& operator=(image&&) noexcept;
    ~image();

    int width() const;
    int height() const;

private:
    explicit image(std::unique_ptr<image_impl>&&) noexcept;
    friend class image_impl;
    std::unique_ptr<image_impl> m_impl;
};

}

#endif
