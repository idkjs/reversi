open Jest;
open Enzyme;
open Expect;

configureEnzyme(react_17_adapter())|>ignore;

describe("<App />", () => {
    test("should render a Game with game prop", () => {
        let game = Game.init([||]);
        let wrapper = shallow(<App game />);

        expect(wrapper |> Enzyme.Shallow.find("Game") |> Enzyme.Shallow.length) |> toBe(1);
    });
});
