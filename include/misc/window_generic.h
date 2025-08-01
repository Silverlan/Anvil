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

/** Implements a simple window wrapper for Windows environments.
 *
 *  NOTE: This wrapper does not support scaling (yet).
 **/
#ifndef WINDOW_GENERIC_H
#define WINDOW_GENERIC_H

#include "misc/window.h"

namespace Anvil
{
    class WindowGeneric : public Window
    {
    public:
		enum class Type : uint8_t {
			Win32 = 0,
			Xcb,
			Wayland,
			Windowless,

			Count,
		};
		union Handle {
			void *win32Window;
			void *waylandWindow;
			uint32_t xcbWindow;
		};
		using Connection = void*;
		using Display = void*;
        static Anvil::WindowUniquePtr create(Type type, Handle handle, Display display, Connection connection, uint32_t width, uint32_t height, bool visible, uint32_t fbWidth, uint32_t fbHeight);

        virtual ~WindowGeneric() { /* Stub */ }

        virtual void close() override;
        virtual void run() override;

        /* Returns window's platform */
        WindowPlatform get_platform() const
        {
            return WINDOW_PLATFORM_GENERIC;
        }

        bool is_dummy()
        {
            return false;
        }

        /* This function should never be called under Windows */
        virtual void* get_connection() const override { return m_connection; }
		Type get_type() const { return m_type; }
		Display get_display() const { return m_display; }
        Handle get_generic_handle() const { return m_handle; }
        uint32_t get_framebuffer_width() const { return m_fbWidth; }
        uint32_t get_framebuffer_height() const { return m_fbHeight; }
        void set_framebuffer_size(uint32_t in_width, uint32_t in_height)
        {
            m_fbWidth = in_width;
            m_fbHeight = in_height;
        }

        /** Changes the window title.
         *
         *  @param in_new_title Null-terminated string, holding the new title.
         */
        void set_title(const std::string& in_new_title) override;

    private:
        /* Private functions */

        WindowGeneric(Type type,
			          Handle handle,
			          const std::string             &in_title,
                      Display                       display,
		              Connection                    connection,
                      unsigned int                   in_width,
                      unsigned int                   in_height,
                      uint32_t                      fbWidth,
                      uint32_t                      fbHeight,
                      PresentCallbackFunction        in_present_callback_func);

        /** Creates a new system window and prepares it for usage. */
        bool init(const bool& in_visible);

        /* Private variables */
		Type m_type;
		Display m_display;
		Connection m_connection;
        Handle m_handle;
        uint32_t m_fbWidth;
        uint32_t m_fbHeight;
    };
}; /* namespace Anvil */

#endif /* WINDOW_WIN3264_H */

