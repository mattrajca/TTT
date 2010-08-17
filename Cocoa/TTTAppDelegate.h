//
//  TTTAppDelegate.h
//  TTT
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "BoardView.h"

@interface TTTAppDelegate : NSObject < NSApplicationDelegate, BoardViewDelegate > {
  @private
    NSWindow *_window;
	BoardView *_boardView;
}

@property (nonatomic, assign) IBOutlet NSWindow *window;
@property (nonatomic, assign) IBOutlet BoardView *boardView;

@end
