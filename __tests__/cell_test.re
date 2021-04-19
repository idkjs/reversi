open Jest;
open Enzyme;
open Expect;

let _ = Enzyme.configureEnzyme(react_17_adapter());

describe("<Cell />", () => {
    test("should render a disk with the right identifier", () => {
        let test = (color, expectedClass) => {
            let wrapper = shallow(
                <Cell
                    color
                    onClick=((_) => ())
                />
            );

            expect(wrapper |> Renderer.find(expectedClass) |> Renderer.length) |> toBe(1);
        };

        test(Some(Cell.Black), ".cell.black")|>ignore;
        test(Some(Cell.White), ".cell.white")|>ignore;
        test(None, ".cell");
    });
});
