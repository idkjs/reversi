type player = {
  name: string,
  color: Cell.color,
};

let bullet = player =>
  switch (player.color) {
  | Cell.Black => {js|•|js}
  | Cell.White => {js|○|js}
  };

[@react.component]
let make = (~player, ~current) => {
  <div className={"player" ++ (current ? " current" : "")}>
    {React.string(player.name)}
    {React.string(" " ++ bullet(player))}
  </div>;
};
