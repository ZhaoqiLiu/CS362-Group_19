// LAF OS Library
// Copyright (C) 2012-2017  David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <Cocoa/Cocoa.h>

#include "os/osx/app_delegate.h"

#include "base/fs.h"
#include "os/event.h"
#include "os/event_queue.h"
#include "os/osx/app.h"
#include "os/osx/generate_drop_files.h"
#include "os/osx/view.h"
#include "os/system.h"

@implementation OSXNSApplication

- (void)sendEvent:(NSEvent *)event
{
  if ([event type] == NSKeyDown) {
    if (([event modifierFlags] & NSDeviceIndependentModifierFlagsMask) == NSCommandKeyMask) {
      if ([[event charactersIgnoringModifiers] isEqualToString:@"x"]) {
        if ([self sendAction:@selector(cut:) to:nil from:self])
          return;
      }
      else if ([[event charactersIgnoringModifiers] isEqualToString:@"c"]) {
        if ([self sendAction:@selector(copy:) to:nil from:self])
          return;
      }
      else if ([[event charactersIgnoringModifiers] isEqualToString:@"v"]) {
        if ([self sendAction:@selector(paste:) to:nil from:self])
          return;
      }
      else if ([[event charactersIgnoringModifiers] isEqualToString:@"z"]) {
        if ([self sendAction:@selector(undo:) to:nil from:self])
          return;
      }
      else if ([[event charactersIgnoringModifiers] isEqualToString:@"a"]) {
        if ([self sendAction:@selector(selectAll:) to:nil from:self])
          return;
      }
    }
    else if (([event modifierFlags] & NSDeviceIndependentModifierFlagsMask) == (NSCommandKeyMask | NSShiftKeyMask)) {
      if ([[event charactersIgnoringModifiers] isEqualToString:@"Z"]) {
        if ([self sendAction:@selector(redo:) to:nil from:self])
          return;
      }
    }
  }
  [super sendEvent:event];
}

@end

@protocol OSXValidateMenuItemProtocol
- (void)validateMenuItem;
@end

@implementation OSXAppDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
  os::Event ev;
  ev.setType(os::Event::CloseDisplay);
  os::queue_event(ev);
  return NSTerminateCancel;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app
{
  return YES;
}

- (void)applicationWillTerminate:(NSNotification*)notification
{
}

- (void)applicationWillResignActive:(NSNotification*)notification
{
  NSEvent* event = [NSApp currentEvent];
  if (event != nil)
    [OSXView updateKeyFlags:event];
}

- (void)applicationDidBecomeActive:(NSNotification*)notification
{
  NSEvent* event = [NSApp currentEvent];
  if (event != nil)
    [OSXView updateKeyFlags:event];
}

- (BOOL)application:(NSApplication*)app openFiles:(NSArray*)filenames
{
  generate_drop_files_from_nsarray(filenames);

  [app replyToOpenOrPrint:NSApplicationDelegateReplySuccess];
  return YES;
}

- (void)executeMenuItem:(id)sender
{
  [sender executeMenuItem:sender];
}

- (BOOL)validateMenuItem:(NSMenuItem*)menuItem
{
  if ([menuItem respondsToSelector:@selector(validateMenuItem)]) {
    [((id<OSXValidateMenuItemProtocol>)menuItem) validateMenuItem];
    return menuItem.enabled;
  }
  else
    return [super validateMenuItem:menuItem];
}

@end
