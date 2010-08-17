const Player = {
	Human: -1,
	None: 0,
	Computer: 1
};

const kBoardWidth = 100;
const kRows = 3, kCols = 3;

const kAlpha = Player.Human;
const kBeta = Player.Computer;

function oppositePlayer (p) {
	return p == Player.Computer ? Player.Human : Player.Computer;
}

function cidx (x, y) {
	return y * 3 + x;
}

function Board() {
	var len = kRows * kCols;
	this.state = new Array(len);
	
	for (var i = 0; i < len; i++) {
		this.state[i] = Player.None;
	}
}

Board.prototype._hasStraightWin = function() {
	for (var n = 0; n < kRows; n++) {
		var midX = this.state[cidx(1,n)];
		var midY = this.state[cidx(n,1)];
		
		if (midX != Player.None) {
			if (this.state[cidx(0,n)] == midX && midX == this.state[cidx(2,n)])
				return true;
		}
		
		if (midY != Player.None) {
			if (this.state[cidx(n,0)] == midY && midY == this.state[cidx(n,2)])
				return true;
		}
	}
	
	return false;
}

Board.prototype._hasDiagonalWin = function () {
	var mid = this.state[cidx(1,1)]
	
	if (mid == Player.None)
		return false;
	
	if ((this.state[cidx(0,0)] == mid && mid == this.state[cidx(2,2)]) || 
		(this.state[cidx(0,2)] == mid && mid == this.state[cidx(2,0)])) {
		
		return true;
	}
	
	return false;
}

Board.prototype._minimax = function (player, alpha, beta) {
	if (this.hasWin())
		return oppositePlayer(player);
	
	else if (this.isFull())
		return Player.None;
	
	for (var x = 0; x < kCols; x++) {
		for (var y = 0; y < kRows; y++) {
			if (this.state[cidx(x,y)] == Player.None) {
				this.state[cidx(x,y)] = player;
				
				var v = this._minimax (oppositePlayer(player), alpha, beta);
				this.state[cidx(x,y)] = Player.None;
				
				if (player == Player.Computer && v > alpha) {
					alpha = v;
					
					if (alpha >= beta)
						return alpha;
				}
				else if (player == Player.Human && v < beta) {
					beta = v;
					
					if (alpha >= beta)
						return beta;
				}
			}
		}
	}
	
	return player == Player.Computer ? alpha : beta;
}

Board.prototype.isFull = function () {
	for (var x = 0; x < kCols; x++) {
		for (var y = 0; y < kRows; y++) {
			if (this.state[cidx(x,y)] == Player.None)
				return false;
		}
	}
	
	return true;
}

Board.prototype.hasWin = function() {
	return this._hasStraightWin() || this._hasDiagonalWin();
}

Board.prototype.playerAtCoordinate = function (x, y) {
	return this.state[cidx(x,y)];
}

Board.prototype.setPlayerAtCoordinate = function (x, y, player) {
	this.state[cidx(x,y)] = player;
}

Board.prototype.findBestComputerMove = function() {
	var score = kAlpha, bestX = 0, bestY = 0;
	
	for (var x = 0; x < kCols; x++) {
		for (var y = 0; y < kRows; y++) {
			if (this.state[cidx(x,y)] == Player.None) {
				this.state[cidx(x,y)] = Player.Computer;
				
				var v = this._minimax (Player.Human, kAlpha, kBeta);
				this.state[cidx(x,y)] = Player.None;
				
				if (v > score) {
					score = v, bestX = x, bestY = y;
				}
			}
		}
	}
	
	return { x: bestX, y: bestY };
}
