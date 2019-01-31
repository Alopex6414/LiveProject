// Copyright (c) 2018 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=6c88144cb4388bd640b52d35d78fc45c682cb333$
//

#ifndef CEF_INCLUDE_CAPI_VIEWS_CEF_LABEL_BUTTON_CAPI_H_
#define CEF_INCLUDE_CAPI_VIEWS_CEF_LABEL_BUTTON_CAPI_H_
#pragma once

#include "include/capi/cef_image_capi.h"
#include "include/capi/views/cef_button_capi.h"
#include "include/capi/views/cef_button_delegate_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _cef_menu_button_t;

///
// LabelButton is a button with optional text and/or icon. Methods must be
// called on the browser process UI thread unless otherwise indicated.
///
typedef struct _cef_label_button_t {
  ///
  // Base structure.
  ///
  cef_button_t base;

  ///
  // Returns this LabelButton as a MenuButton or NULL if this is not a
  // MenuButton.
  ///
  struct _cef_menu_button_t*(CEF_CALLBACK* as_menu_button)(
      struct _cef_label_button_t* self);

  ///
  // Sets the text shown on the LabelButton. By default |text| will also be used
  // as the accessible name.
  ///
  void(CEF_CALLBACK* set_text)(struct _cef_label_button_t* self,
                               const cef_string_t* text);

  ///
  // Returns the text shown on the LabelButton.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_text)(
      struct _cef_label_button_t* self);

  ///
  // Sets the image shown for |button_state|. When this Button is drawn if no
  // image exists for the current state then the image for
  // CEF_BUTTON_STATE_NORMAL, if any, will be shown.
  ///
  void(CEF_CALLBACK* set_image)(struct _cef_label_button_t* self,
                                cef_button_state_t button_state,
                                struct _cef_image_t* image);

  ///
  // Returns the image shown for |button_state|. If no image exists for that
  // state then the image for CEF_BUTTON_STATE_NORMAL will be returned.
  ///
  struct _cef_image_t*(CEF_CALLBACK* get_image)(
      struct _cef_label_button_t* self,
      cef_button_state_t button_state);

  ///
  // Sets the text color shown for the specified button |for_state| to |color|.
  ///
  void(CEF_CALLBACK* set_text_color)(struct _cef_label_button_t* self,
                                     cef_button_state_t for_state,
                                     cef_color_t color);

  ///
  // Sets the text colors shown for the non-disabled states to |color|.
  ///
  void(CEF_CALLBACK* set_enabled_text_colors)(struct _cef_label_button_t* self,
                                              cef_color_t color);

  ///
  // Sets the font list. The format is "<FONT_FAMILY_LIST>,[STYLES] <SIZE>",
  // where: - FONT_FAMILY_LIST is a comma-separated list of font family names, -
  // STYLES is an optional space-separated list of style names (case-sensitive
  //   "Bold" and "Italic" are supported), and
  // - SIZE is an integer font size in pixels with the suffix "px".
  //
  // Here are examples of valid font description strings: - "Arial, Helvetica,
  // Bold Italic 14px" - "Arial, 14px"
  ///
  void(CEF_CALLBACK* set_font_list)(struct _cef_label_button_t* self,
                                    const cef_string_t* font_list);

  ///
  // Sets the horizontal alignment; reversed in RTL. Default is
  // CEF_HORIZONTAL_ALIGNMENT_CENTER.
  ///
  void(CEF_CALLBACK* set_horizontal_alignment)(
      struct _cef_label_button_t* self,
      cef_horizontal_alignment_t alignment);

  ///
  // Reset the minimum size of this LabelButton to |size|.
  ///
  void(CEF_CALLBACK* set_minimum_size)(struct _cef_label_button_t* self,
                                       const cef_size_t* size);

  ///
  // Reset the maximum size of this LabelButton to |size|.
  ///
  void(CEF_CALLBACK* set_maximum_size)(struct _cef_label_button_t* self,
                                       const cef_size_t* size);
} cef_label_button_t;

///
// Create a new LabelButton. A |delegate| must be provided to handle the button
// click. |text| will be shown on the LabelButton and used as the default
// accessible name. If |with_frame| is true (1) the button will have a visible
// frame at all times, center alignment, additional padding and a default
// minimum size of 70x33 DIP. If |with_frame| is false (0) the button will only
// have a visible frame on hover/press, left alignment, less padding and no
// default minimum size.
///
CEF_EXPORT cef_label_button_t* cef_label_button_create(
    struct _cef_button_delegate_t* delegate,
    const cef_string_t* text,
    int with_frame);

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_VIEWS_CEF_LABEL_BUTTON_CAPI_H_
