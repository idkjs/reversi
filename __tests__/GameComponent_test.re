open Jest;

Enzyme.configureEnzyme(Enzyme.react_17_adapter()) |> ignore;

let matrixToCells = matrix =>
  Array.(
    mapi((y, row) => mapi((x, color) => Cell.{x, y, color}, row), matrix)
    |> fold_left(append, [||])
    |> to_list
    |> Board.sortCells
  );

let (w, b, n) = (Some(Cell.White), Some(Cell.Black), None);

let fakeGame =
  Game.init([|
    {name: "foo", color: Cell.Black},
    {name: "bar", color: Cell.White},
  |]);


describe("Full DOM rendering", () => {
  // let setup = (~title="Test", ()) => Enzyme.mount(<GameComponent title />);
  // let initialState: Game.state = {game: fakeGame, message: Some("foo")};

  // let setup = (~title="Test", ()) =>
  //   Enzyme.shallow(<GameComponent initialState title />);

  describe("Game", () => {
    describe("currentPlayer", () => {
      Expect.(
        test("should return current player for game", () => {
          expect(Game.currentPlayer(fakeGame))
          |> toEqual(Player.{name: "foo", color: Cell.Black})
        })
      )
    })
  });
  describe("playerCanPlay", () => {
    open Expect;

    test("should return true if player can place cell change", () => {
      expect(Game.playerCanPlay(fakeGame, 0)) |> toBe(true)
    });

    test("should return false if player can't place cell change", () => {
      expect(Game.playerCanPlay({...fakeGame, board: Board.init(2, 2)}, 0))
      |> toBe(false)
    });
  });

  describe("switchPlayer", () => {
    open Expect;
    test("should return a switched game if player can play", () => {
      let originPlayerIndex = fakeGame.playerIndex;

      expect(Game.switchPlayer(fakeGame).playerIndex)
      |> not_
      |> toBe(originPlayerIndex);
    });

    test("should raise CantSwitchPlayer if player can't be switched", () => {
      let gameWithoutMove = {
        ...fakeGame,
        board: {
          width: 4,
          height: 4,
          cells:
            matrixToCells([|
              [|b, w, n, n|],
              [|n, w, n, n|],
              [|n, n, n, n|],
              [|n, n, n, n|],
            |]),
        },
      };

      expect(() =>
        Game.switchPlayer(gameWithoutMove)
      ) |> toThrow;
      // |> toThrowException(Game.CantSwitchPlayer(gameWithoutMove))
    });

    test(
      "should raise InsolubleGame with finished game if there's no possible cell change",
      () => {
        let gameWithoutSolution = {...fakeGame, board: Board.init(2, 2)};

        expect(() =>
          Game.switchPlayer(gameWithoutSolution)
        ) |> toThrow;
        // |> toThrowException(Game.InsolubleGame({
        //     ...gameWithoutSolution,
        //     finished: true
        // }))
      },
    );
  });
  describe("applyCellClick", () => {
    open Expect;

    test("should return finished game if last cell change", () => {
      let game = {
        ...fakeGame,
        board: {
          ...Board.init(3, 3),
          cells: matrixToCells([|[|w, w, w|], [|n, w, b|], [|w, w, w|]|]),
        },
      };

      expect(Game.applyCellClick(game, 0, 1))
      |> toEqual({...game, finished: true});
    });

    test("should return game with switched player instead", () => {
      let game = {
        ...fakeGame,
        board: {
          ...Board.init(4, 4),
          cells:
            matrixToCells([|
              [|n, n, n, n|],
              [|n, b, w, n|],
              [|n, w, b, n|],
              [|n, n, n, n|],
            |]),
        },
      };

      expect(Game.applyCellClick(game, 1, 3).playerIndex) |> toEqual(1);
    });
  });
});
