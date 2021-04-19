// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Jest from "@glennsl/bs-jest/src/jest.bs.js";
import * as React from "react";
import * as Enzyme from "bs-enzyme/src/Enzyme.bs.js";
import * as Player from "../src/Player.bs.js";
import * as Enzyme$1 from "enzyme";
import * as EnzymeAdapterReact from "@wojtekmaj/enzyme-adapter-react-17";

Enzyme.configureEnzyme(new EnzymeAdapterReact());

Jest.describe("Player", (function (param) {
        Jest.describe("bullet", (function (param) {
                Jest.test("should return the right bullet icon for Black color", (function (param) {
                        return Jest.Expect.toBe("•", Jest.Expect.expect(Player.bullet({
                                            name: "foo",
                                            color: /* Black */1
                                          })));
                      }));
                return Jest.test("should return the right bullet icon for White color", (function (param) {
                              return Jest.Expect.toBe("○", Jest.Expect.expect(Player.bullet({
                                                  name: "foo",
                                                  color: /* White */0
                                                })));
                            }));
              }));
        return Jest.describe("<Player />", (function (param) {
                      Jest.test("should render the player name", (function (param) {
                              var wrapper = Enzyme$1.shallow(React.createElement(Player.make, {
                                        player: {
                                          name: "John",
                                          color: /* Black */1
                                        },
                                        current: false
                                      }));
                              return Jest.Expect.toEqual("John " + "•", Jest.Expect.expect(wrapper.find(".player").text()));
                            }));
                      Jest.test("should render current as className if current", (function (param) {
                              var wrapper = Enzyme$1.shallow(React.createElement(Player.make, {
                                        player: {
                                          name: "John",
                                          color: /* Black */1
                                        },
                                        current: true
                                      }));
                              return Jest.Expect.toBe(1, Jest.Expect.expect(wrapper.find(".player.current").length));
                            }));
                      return Jest.test("should not render current as className if not current", (function (param) {
                                    var wrapper = Enzyme$1.shallow(React.createElement(Player.make, {
                                              player: {
                                                name: "John",
                                                color: /* Black */1
                                              },
                                              current: false
                                            }));
                                    return Jest.Expect.toBe(0, Jest.Expect.expect(wrapper.find(".player.current").length));
                                  }));
                    }));
      }));

export {
  
}
/*  Not a pure module */