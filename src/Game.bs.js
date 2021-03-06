// Generated by ReScript, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Board from "./Board.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Player from "./Player.bs.js";
import * as Caml_array from "bs-platform/lib/es6/caml_array.js";
import * as Caml_exceptions from "bs-platform/lib/es6/caml_exceptions.js";
import * as Caml_js_exceptions from "bs-platform/lib/es6/caml_js_exceptions.js";

var CantSwitchPlayer = /* @__PURE__ */Caml_exceptions.create("Game.CantSwitchPlayer");

var InsolubleGame = /* @__PURE__ */Caml_exceptions.create("Game.InsolubleGame");

function currentPlayer(game) {
  return Caml_array.get(game.players, game.playerIndex);
}

function init(players) {
  return {
          board: Board.init(8, 8),
          players: players,
          playerIndex: 0,
          finished: false
        };
}

function playerCanPlay(game, playerIndex) {
  var color = Caml_array.get(game.players, playerIndex).color;
  var match = Board.availableCellChanges(game.board, color);
  if (match) {
    return true;
  } else {
    return false;
  }
}

function switchPlayer(game) {
  var nextPlayerIndex = game.playerIndex === 1 ? 0 : 1;
  if (playerCanPlay(game, nextPlayerIndex)) {
    return {
            board: game.board,
            players: game.players,
            playerIndex: nextPlayerIndex,
            finished: game.finished
          };
  }
  if (playerCanPlay(game, game.playerIndex)) {
    throw {
          RE_EXN_ID: CantSwitchPlayer,
          _1: game,
          Error: new Error()
        };
  }
  throw {
        RE_EXN_ID: InsolubleGame,
        _1: {
          board: game.board,
          players: game.players,
          playerIndex: game.playerIndex,
          finished: true
        },
        Error: new Error()
      };
}

function applyCellClick(game, x, y) {
  var color = currentPlayer(game).color;
  var board = Board.applyCellChange(game.board, {
        x: x,
        y: y,
        color: color
      });
  var match = Board.getCountForColor(board, undefined);
  if (match !== 0) {
    return switchPlayer({
                board: board,
                players: game.players,
                playerIndex: game.playerIndex,
                finished: game.finished
              });
  } else {
    return {
            board: game.board,
            players: game.players,
            playerIndex: game.playerIndex,
            finished: true
          };
  }
}

function locationReload(param) {
  return (window.location.reload());
}

function reducer(state, action) {
  if (action) {
    var game;
    try {
      game = applyCellClick(state.game, action._0, action._1);
    }
    catch (raw_game){
      var game$1 = Caml_js_exceptions.internalToOCamlException(raw_game);
      if (game$1.RE_EXN_ID === Board.InvalidMove) {
        return {
                game: state.game,
                message: "Invalid Move"
              };
      }
      if (game$1.RE_EXN_ID === InsolubleGame) {
        return {
                game: game$1._1,
                message: "No One Can Play"
              };
      }
      if (game$1.RE_EXN_ID === CantSwitchPlayer) {
        return {
                game: game$1._1,
                message: "Opponent can't play, play again!"
              };
      }
      throw game$1;
    }
    return {
            game: game,
            message: undefined
          };
  }
  locationReload(undefined);
  return state;
}

function Game(Props) {
  var game = Props.game;
  var match = React.useReducer(reducer, {
        game: game,
        message: undefined
      });
  var state = match[0];
  var message = state.message;
  var game$1 = state.game;
  var dispatch = match[1];
  var messageElement = message !== undefined ? message : null;
  return React.createElement("div", {
              className: "game"
            }, messageElement, React.createElement(Board.make, {
                  board: game$1.board,
                  onCellClick: (function (param) {
                      return Curry._1(dispatch, /* Click */{
                                  _0: param.x,
                                  _1: param.y
                                });
                    })
                }), React.createElement("div", {
                  className: "players"
                }, $$Array.mapi((function (i, player) {
                        return React.createElement(Player.make, {
                                    player: player,
                                    current: game$1.playerIndex === i,
                                    key: String(i)
                                  });
                      }), game$1.players)), game$1.finished ? React.createElement("div", {
                    className: "finished"
                  }, "Game Over", React.createElement("br", undefined), React.createElement("button", {
                        onClick: (function (param) {
                            return Curry._1(dispatch, /* Restart */0);
                          })
                      }, "Start Another Game")) : null);
}

var make = Game;

export {
  CantSwitchPlayer ,
  InsolubleGame ,
  currentPlayer ,
  init ,
  playerCanPlay ,
  switchPlayer ,
  applyCellClick ,
  locationReload ,
  reducer ,
  make ,
  
}
/* Board Not a pure module */
