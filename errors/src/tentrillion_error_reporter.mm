#import "tentrillion_error_reporter.hpp"
#include <AppKit/AppKit.h>
#include <AppKit/NSAlert.h>
#import <Cocoa/Cocoa.h>
#include <Foundation/Foundation.h>
#include <Foundation/NSString.h>
#include <cstring>
#include <sstream>
#include <stdio.h>

constexpr const char *tentrillion_error_reporter_title =
	"TenTrillion Game Engine Error Reporter";

bool check_if_launched_by_parent_tentrillion() { // TODO
 return false; }

void show_error_box(const char *description) {
	@autoreleasepool {
		[NSApplication sharedApplication];

		[NSApp activateIgnoringOtherApps:true];

		NSAlert *alert = [[NSAlert alloc] init];
		[alert setMessageText:[NSString stringWithUTF8String:
											tentrillion_error_reporter_title]];
		[alert setInformativeText:[NSString stringWithUTF8String:description]];
		[alert addButtonWithTitle:[NSString stringWithUTF8String:ok_button]];
		[alert addButtonWithTitle:
				   [NSString stringWithUTF8String:send_bug_report_button]];
		[alert setAlertStyle:NSAlertStyleCritical];

		NSModalResponse response = [alert runModal];

		if (response != NSAlertSecondButtonReturn)
			return;
		NSURLComponents *components = [[NSURLComponents alloc] init];

        // Objective C++ is interesting to say the least.
		components.scheme = @"mailto";
		components.path =
			[NSString stringWithUTF8String:recipient_email_address];

		NSMutableArray<NSURLQueryItem *> *query_items = [NSMutableArray array];

		char buffer[100 + sizeof(description)];
		snprintf(buffer, sizeof(buffer), "Bug Report About: %s", description);

		NSString *ns_subject = [NSString stringWithUTF8String:buffer];
		[query_items addObject:[NSURLQueryItem queryItemWithName:@"subject"
														   value:ns_subject]];
		components.queryItems = query_items;

		[[NSWorkspace sharedWorkspace] openURL:components.URL];
	}
}

int main(int argc, char *argv[]) {
	if (!check_if_launched_by_parent_tentrillion())
		show_error_box(not_launched_from_parent_default);

	return 0;
}