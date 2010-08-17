//
//  BoardView.h
//  TTT
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "Board.h"

@protocol BoardViewDelegate;

@interface BoardView : NSView {
  @private
	BoardRef _board;
	__weak id < BoardViewDelegate > _delegate;
}

@property (nonatomic, assign) __weak id < BoardViewDelegate > delegate;

- (void)newGame;

@end


@protocol BoardViewDelegate < NSObject >

- (void)boardView:(BoardView *)boardView gameDidEndWithPlayer:(Player)player;

@end
