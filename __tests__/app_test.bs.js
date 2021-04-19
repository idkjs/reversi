// Generated by ReScript, PLEASE EDIT WITH CARE

import * as App from "../src/App.bs.js";
import * as Game from "../src/Game.bs.js";
import * as Jest from "@glennsl/bs-jest/src/jest.bs.js";
import * as React from "react";
import * as Enzyme from "bs-enzyme/src/Enzyme.bs.js";
import * as Enzyme$1 from "enzyme";
import * as EnzymeAdapterReact from "@wojtekmaj/enzyme-adapter-react-17";

Enzyme.configureEnzyme(new EnzymeAdapterReact());

Jest.describe("<App />", (function (param) {
        return Jest.test("should render a Game with game prop", (function (param) {
                      var game = Game.init([]);
                      var wrapper = Enzyme$1.shallow(React.createElement(App.make, {
                                game: game
                              }));
                      return Jest.Expect.toBe(1, Jest.Expect.expect(wrapper.find("Game").length));
                    }));
      }));

export {
  
}
/*  Not a pure module */