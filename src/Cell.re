type color =
  | White
  | Black;

type cell = {
  x: int,
  y: int,
  color: option(color),
};

[@react.component]
let make = (~color, ~onClick) => {
  let identifier =
    switch (color) {
    | Some(Black) => "black"
    | Some(White) => "white"
    | None => ""
    };

  <div className={"cell " ++ identifier} onClick />;
};
