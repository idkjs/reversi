open Jest;
open Enzyme;
open Expect;
let _ = Enzyme.configureEnzyme(react_17_adapter());

describe("<App />", () => {
    test("should render a Game with game prop", () => {
        let game = Game.init([||]);
        let wrapper = shallow(<App game />);

        expect(wrapper |> Renderer.find("Game") |> Renderer.length) |> toBe(1);
    });
});
