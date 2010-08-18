//
//  BoardView.m
//  TTT
//
//  Copyright Matt Rajca 2010. All rights reserved.
//

#import "BoardView.h"

@interface BoardView ()

- (void)drawGrid;
- (void)drawState;

@end


@implementation BoardView

#define BOX_STROKE 2.0f
#define BOX_WIDTH 100.0f

@synthesize delegate = _delegate;

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        _board = BoardCreate();
    }
    return self;
}

- (BOOL)isFlipped {
	return YES;
}

- (void)drawGrid {
	CGFloat height = [self bounds].size.height;
	
	[[NSColor grayColor] set];
	
	for (int x = 1; x < TTT_COLS; x++) {
		NSRectFill(NSMakeRect(x * BOX_WIDTH, 0.0f, BOX_STROKE, height));
	}
	
	for (int y = 1; y < TTT_ROWS; y++) {
		NSRectFill(NSMakeRect(0.0f, y * BOX_WIDTH, height, BOX_STROKE));
	}
}

- (void)drawState {
	for (int x = 0; x < TTT_COLS; x++) {
		for (int y = 0; y < TTT_ROWS; y++) {
			Player player = BoardPlayerAtCoordinate(_board, x, y);
			NSRect area = NSMakeRect(x * BOX_WIDTH, y * BOX_WIDTH + 6.0f, BOX_WIDTH, BOX_WIDTH);
			
			NSMutableDictionary *attr = [[NSMutableDictionary alloc] init];
			[attr setObject:[NSFont boldSystemFontOfSize:70] forKey:NSFontAttributeName];
			
			NSMutableParagraphStyle *p = [[NSMutableParagraphStyle alloc] init];
			[p setAlignment:NSCenterTextAlignment];
			
			[attr setObject:p forKey:NSParagraphStyleAttributeName];
			
			if (player == PlayerHuman) {
				[@"X" drawInRect:area withAttributes:attr];
			}
			else if (player == PlayerComputer) {
				[@"O" drawInRect:area withAttributes:attr];
			}
		}
	}
}

- (void)drawRect:(NSRect)dirtyRect {
    [[NSColor controlColor] set];
	NSRectFill(dirtyRect);
	
	[self drawGrid];
	[self drawState];
}

- (void)mouseDown:(NSEvent *)theEvent {
	NSPoint pt = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	int x = floor(pt.x / BOX_WIDTH);
	int y = floor(pt.y / BOX_WIDTH);
	
	if (BoardPlayerAtCoordinate(_board, x, y) != PlayerNone) {
		NSBeep();
		return;
	}
	
	BoardSetPlayerAtCoordinate(_board, x, y, PlayerHuman);
	
	Player winner = -2;
	
	if (BoardHasWin(_board))
		winner = PlayerHuman;
	else if (BoardIsFull(_board))
		winner = PlayerNone;
	else {
		Coordinate c = BoardFindBestComputerMove(_board);
		BoardSetPlayerAtCoordinate(_board, c.x, c.y, PlayerComputer);
		
		if (BoardHasWin(_board))
			winner = PlayerComputer;
		else if (BoardIsFull(_board))
			winner = PlayerNone;
	}
	
	[self setNeedsDisplay:YES];
	
	if (winner != -2 && [_delegate respondsToSelector:@selector(boardView:gameDidEndWithPlayer:)]) {
		[_delegate boardView:self gameDidEndWithPlayer:winner];
	}
}

- (void)newGame {
	BoardRelease(_board), _board = NULL;
	_board = BoardCreate();
	
	[self setNeedsDisplay:YES];
}

- (void)finalize {
	BoardRelease(_board);
	
	[super finalize];
}

@end
