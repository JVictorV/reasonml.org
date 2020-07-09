open Util.ReactStuff;
open Ansi;

type colorTarget =
  | Fg
  | Bg;

let mapColor = (~target: colorTarget, c: Color.t): string => {
  switch (target, c) {
  | (Fg, Black) => "text-black"
  | (Fg, Red) => "text-fire"
  | (Fg, Green) => "text-dark-code-3"
  | (Fg, Yellow) => "text-dark-code-1"
  | (Fg, Blue) => "text-dark-code-2"
  | (Fg, Magenta) => "text-berry"
  | (Fg, Cyan) => "text-dark-code-2"
  | (Fg, White) => "text-snow-dark"
  | (Bg, Black) => "bg-black"
  | (Bg, Red) => "bg-fire"
  | (Bg, Green) => "bg-dark-code-3"
  | (Bg, Yellow) => "bg-dark-code-1"
  | (Bg, Blue) => "bg-dark-code-2"
  | (Bg, Magenta) => "bg-berry"
  | (Bg, Cyan) => "bg-dark-code-2"
  | (Bg, White) => "bg-snow-dark"
  };
};

let renderSgrString = (sgrStr: SgrString.t): React.element => {
  let {SgrString.content, params} = sgrStr;

  let className =
    Belt.Array.reduce(params, "", (acc, p) => {
      switch (p) {
      | Sgr.Bold => acc ++ " bold"
      | Fg(c) => acc ++ " " ++ mapColor(~target=Fg, c)
      | Bg(c) => acc ++ " " ++ mapColor(~target=Bg, c)
      | _ => acc
      }
    });

  <span className> content->s </span>;
};


let renderLine = (tokens: array(Lexer.token)): React.element => {
  // Note: pre is essential here, otherwise whitespace and newlines are not respected
  <pre>
    {SgrString.fromTokens(tokens)->Belt.Array.map(renderSgrString)->ate}
  </pre>;
};

/*
   Renders an array of ANSI encoded strings
   and applying the right styling for our design system
 */
[@react.component]
let make = (~className=?, ~children: array(string)) => {
  let lines = Belt.Array.map(children, line => line->Ansi.parse->renderLine);
  <div ?className> lines->ate </div>;
};