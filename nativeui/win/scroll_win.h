// Copyright 2016 Cheng Zhao. All rights reserved.
// Use of this source code is governed by the license that can be found in the
// LICENSE file.

#ifndef NATIVEUI_WIN_SCROLL_WIN_H_
#define NATIVEUI_WIN_SCROLL_WIN_H_

#include <memory>
#include <vector>

#include "nativeui/gfx/geometry/insets.h"
#include "nativeui/scroll.h"
#include "nativeui/win/container_win.h"

namespace nu {

class ScrollBarView;

// The implementation for the Scroll view.
class ScrollView : public ContainerView,
                   public ContainerView::Delegate {
 public:
  explicit ScrollView(Scroll* delegate);

  void SetOrigin(const Vector2d& origin);
  void SetContentSize(const Size& size);
  void SetScrollBarPolicy(Scroll::Policy h_policy, Scroll::Policy v_policy);

  Rect GetViewportRect() const;
  void OnScroll(int x, int y);

  // ContainerView::Delegate:
  void Layout() override;
  std::vector<BaseView*> GetChildren() override;

  // BaseView:
  void SizeAllocate(const Rect& size_allocation) override;
  bool OnMouseWheel(bool vertical, UINT flags, int delta,
                    const Point& point) override;
  void Draw(PainterWin* painter, const Rect& dirty) override;

  Scroll::Policy h_policy() const { return h_policy_; }
  Scroll::Policy v_policy() const { return v_policy_; }
  Vector2d origin() const { return origin_; }
  Scroll* delegate() const { return delegate_; }

 private:
  void UpdateScrollbar();
  bool UpdateOrigin(Vector2d new_origin);
  Rect GetScrollBarRect(bool vertical) const;
  void DrawScrollBar(bool vertical, PainterWin* painter, const Rect& dirty);

  Size content_size_;
  Vector2d origin_;

  // The height of scrollbar.
  int scrollbar_height_;

  // The policy of showing scrollbar.
  Scroll::Policy h_policy_;
  Scroll::Policy v_policy_;

  std::unique_ptr<ScrollBarView> h_scrollbar_;
  std::unique_ptr<ScrollBarView> v_scrollbar_;

  Scroll* delegate_;
};

}  // namespace nu

#endif  // NATIVEUI_WIN_SCROLL_WIN_H_
