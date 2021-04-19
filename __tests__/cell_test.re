open Jest;
open Enzyme;
open Expect;

configureEnzyme(react_17_adapter())|>ignore;

describe("<Cell />", () => {
    test("should render a disk with the right identifier", () => {
        let test = (color, expectedClass) => {
            let wrapper = shallow(
                <Cell
                    color
                    onClick=((_) => ())
                />
            );

            expect(wrapper |> Enzyme.Shallow.find(expectedClass) |> Enzyme.Shallow.length) |> toBe(1);
        };

        test(Some(Cell.Black), ".cell.black")|>ignore;
        test(Some(Cell.White), ".cell.white")|>ignore;
        test(None, ".cell");
    });
});
