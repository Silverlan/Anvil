//
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "misc/window_generic.h"
#include <sstream>

/* See create() for documentation */
Anvil::WindowGeneric::WindowGeneric(Type type,
	                                void *windowHandle,
	                                const std::string             &in_title,
                                    unsigned int                   in_width,
                                    unsigned int                   in_height,
                                    Anvil::PresentCallbackFunction in_present_callback_func)
    :Window(in_title,
            in_width,
            in_height,
            true, /* in_closable */
            in_present_callback_func)
{
	m_window = reinterpret_cast<WindowHandle>(windowHandle);
    m_window_owned = false;
	m_type = type;
}

/** Please see header for specification */
Anvil::WindowUniquePtr Anvil::WindowGeneric::create(Type type, void *windowHandle, uint32_t width, uint32_t height, bool visible)
{
    WindowUniquePtr result_ptr (nullptr,
                                std::default_delete<Window>() );
    uint32_t        window_size[2] = {0};

    window_size[0] = width;
	window_size[1] = height;

    /* Go ahead and create the window wrapper instance */
    result_ptr.reset(
        new Anvil::WindowGeneric(type,
			                     windowHandle,
			                     "Generic wrapper window instance",
                                 window_size[0],
                                 window_size[1],
                                 nullptr) /* present_callback_func_ptr */
    );

    if (result_ptr)
    {
        if (!dynamic_cast<WindowGeneric*>(result_ptr.get() )->init(visible))
        {
            result_ptr.reset();
        }
    }

end:
    return result_ptr;
}

void Anvil::WindowGeneric::close() {}

/** Creates a new system window and prepares it for usage. */
bool Anvil::WindowGeneric::init(const bool& in_visible)
{
    bool        result            = false;
    const char* window_class_name = (m_closable) ? "Anvil window (closable)"
                                                 : "Anvil window (non-closable)";

    result = true;
    return result;
}

void Anvil::WindowGeneric::run() {}

void Anvil::WindowGeneric::set_title(const std::string& in_new_title) {}
