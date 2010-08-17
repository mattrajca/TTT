//
//  TTTAppDelegate.m
//  TTT
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "TTTAppDelegate.h"

@implementation TTTAppDelegate

@synthesize window = _window;
@synthesize boardView = _boardView;

- (void)awakeFromNib {
	_boardView.delegate = self;
}

- (void)boardView:(BoardView *)boardView gameDidEndWithPlayer:(Player)player {
	NSString *message = nil;
	
	switch (player) {
		case PlayerNone:
			message = @"Looks like it's a draw! Play again?";
			break;
		case PlayerHuman:
			message = @"You won! How is this possible?";
			break;
		case PlayerComputer:
			message = @"Mr. Macintosh beat you. Play again?";
			break;
		default:
			break;
	}
	
	NSBeginAlertSheet(@"Game over!", @"New Game", @"Quit", nil, _window, self, NULL, @selector(sheetDidDismiss:returnCode:contextInfo:), NULL, message);
}

- (void)sheetDidDismiss:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo {
	if (returnCode == NSAlertDefaultReturn) {
		[_boardView newGame];
	}
	else {
		[NSApp terminate:self];
	}
}

@end
