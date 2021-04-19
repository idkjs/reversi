// type game = Game.game;
open Game;
exception CantSwitchPlayer(game);
exception InsolubleGame(game);

let currentPlayer = game => game.players[game.playerIndex];

let init = players => {
  board: Board.init(8, 8),
  players,
  playerIndex: 0,
  finished: false,
};

let playerCanPlay = (game, playerIndex) => {
  let color = Some(game.players[playerIndex].color);

  switch (Board.availableCellChanges(game.board, color)) {
  | [] => false
  | _ => true
  };
};

let switchPlayer = game => {
  let nextPlayerIndex = game.playerIndex == 1 ? 0 : 1;

  playerCanPlay(game, nextPlayerIndex)
    ? {...game, playerIndex: nextPlayerIndex}
    : playerCanPlay(game, game.playerIndex)
        ? raise(CantSwitchPlayer(game))
        : raise(InsolubleGame({...game, finished: true}));
};

let applyCellClick = (game, x, y) =>
  Board.(
    {
      let color = Some(currentPlayer(game).color);
      let board = applyCellChange(game.board, {x, y, color});

      switch (getCountForColor(board, None)) {
      | 0 => {...game, finished: true}
      | _ => switchPlayer({...game, board})
      };
    }
  );

let locationReload = _ => [%bs.raw {| window.location.reload() |}];

// type action =
//   | Click(int, int)
//   | Restart;

// type state = {
//   game,
//   message: option(string),
// };

let reducer = (state, action) =>
  switch (action) {
  | Click(x, y) =>
    switch (applyCellClick(state.game, x, y)) {
    | game => {game, message: None}
    | exception Board.InvalidMove => {
        ...state,
        message: Some("Invalid Move"),
      }
    | exception (InsolubleGame(game)) => {
        game,
        message: Some("No One Can Play"),
      }
    | exception (CantSwitchPlayer(game)) => {
        game,
        message: Some("Opponent can't play, play again!"),
      }
    }
  | Restart =>
    locationReload() |> ignore;
    state;
  };

[@react.component]
let make = (~title,~initialState) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let {game, message} = state;

  let messageElement =
    switch (message) {
    | None => React.null
    | Some(message) => React.string(message)
    };

  <div className="game">
      <div id="header"> <h1> (React.string(title)) </h1> </div>

    messageElement
    <Board
      board={game.board}
      onCellClick={({x, y}: Cell.cell) => dispatch(Click(x, y))}
    />
    <div className="players">
      {React.array(
         Array.mapi(
           (i, player) =>
             <Player
               player
               key={string_of_int(i)}
               current={game.playerIndex == i}
             />,
           game.players,
         ),
       )}
    </div>
    {game.finished
       ? <div className="finished">
           {React.string("Game Over")}
           <br />
           <button onClick={_ => dispatch(Restart)}>
             {React.string("Start Another Game")}
           </button>
         </div>
       : React.null}
  </div>;
};
