# Scientific Calculator

A scientific calculator built with plain HTML, CSS, and JavaScript no frameworks, no build step, no dependencies. Open the file and it works.

This started as a simple four function calculator and was extended into a full scientific calculator with trigonometry, logarithms, exponents, and a degree/radian toggle.

## Project Overview

The calculator lives in a single `calculator.html` file. The layout is a rounded, dark-themed keypad inspired by physical calculator design: orange buttons for the core operators (+, -, *, /), grey buttons for scientific functions, and a green "=" key that stands out as the primary action.

Unlike a lot of tutorial calculators that evaluate each button press immediately, this one treats the display as a live expression editor. You type out a full expression including nested functions like `sin(30)+sqrt(16)`  and only when you press `=` does it get evaluated. That makes it behave more like a real scientific calculator and less like a running total.

## Features

- **Basic arithmetic** — addition, subtraction, multiplication, division
- **Trigonometric functions** — `sin`, `cos`, `tan`, plus their inverses (`sin⁻¹`, `cos⁻¹`, `tan⁻¹`) behind a `2nd` toggle, with a DEG/RAD switch so results match whichever mode you're working in
- **Logarithms** — base-10 log (`log`) and natural log (`ln`)
- **Powers and roots** — `x^y` for exponents, `x²` for squaring, `√x` for square root, `1/x` for reciprocal
- **Constants** — π and e as one-tap buttons
- **Percentages** — `%` converts to `/100` inline, so `50%` becomes `0.5`
- **Parentheses** — for grouping and controlling order of operations, with automatic closing of any parentheses you forget before pressing `=`
- **ANS** — recalls the result of your last calculation so you can chain expressions
- **Sign toggle (+/-)** — flips the sign of the whole current expression
- **Delete and clear** — `DEL` removes the last character, `C` wipes the expression
- **Error handling** — invalid expressions (like dividing in a way that produces `NaN`/`Infinity`) show a small inline error instead of silently breaking
- **Keyboard support** — you can type digits, operators, Enter, Backspace, and Escape directly from your keyboard, not just click buttons
- **Floating-point cleanup** — results like `0.1 + 0.2` are rounded to avoid showing ugly numbers like `0.30000000000000004`
- **Fully responsive layout** — built with fluid widths, `clamp()`-based type scale, and a small-screen media query, so it resizes cleanly from desktop down to narrow phone screens instead of being fixed at one pixel width

## How It Works

The core of the calculator is one function, `calculate()`, which:

1. Takes whatever string the user has built up (e.g. `sin(30)+2^2`)
2. Auto-closes any parentheses the user didn't bother finishing (`sqrt(16` becomes `sqrt(16)`)
3. Swaps calculator-friendly symbols for real JavaScript (`^` becomes `**`, `%` becomes `/100`)
4. Runs it through a `Function()` constructor with only a handful of math helpers passed in as arguments (`sin`, `cos`, `tan`, `asin`, `acos`, `atan`, `log`, `ln`, `sqrt`, `sqr`, `recip`, `PI`, `E`, `ANS`)
5. Catches anything that throws or comes back as `NaN`/`Infinity` and shows an error instead of crashing

Using `Function()` instead of `eval()` was a deliberate choice — the expression only gets access to the specific math functions handed to it, not the rest of the page's variables or the global scope.

The DEG/RAD toggle works by having `sin`, `cos`, `tan` (and their inverses) route through shared `toRadians()`/`fromRadians()` helpers, which only convert when the calculator is currently in degree mode. Flip the toggle and the same trig functions behave differently without touching the expression itself. The `2nd` button flips a separate `inverseMode` flag that swaps `sin`/`cos`/`tan` for `asin`/`acos`/`atan` — both the button labels and the function actually inserted into the expression change together.

## Programming Concepts Used

- **DOM manipulation** — reading and writing to the display, toggling CSS classes for the active angle mode and inverse mode
- **Event handling** — `onclick` handlers on every button, plus a global `keydown` listener for keyboard input
- **State management** — the calculator keeps track of the current expression string, the active angle mode, whether inverse trig is active, the last computed answer, and whether the last action was a completed calculation, all in a few plain JavaScript variables
- **Function scoping and closures** — the `Function()` constructor is used to safely evaluate math expressions with a restricted, explicit set of variables in scope
- **CSS Grid** — the keypad layout uses `grid-template-columns` to lay out a 5-column button grid, with wide buttons spanning multiple columns and the `=` key spanning the full row
- **Responsive/fluid design** — `clamp()` is used throughout for font sizes and spacing so text and buttons scale smoothly between a small phone and a desktop window, the calculator's width is set with `min(420px, 100%)` so it never overflows a narrow screen, and a media query tightens spacing further below 360px
- **Regular expressions** — used for input validation (e.g. deciding whether a keypress is a valid calculator character) and for string replacement (`^` → `**`, `%` → `/100`)
- **Error handling** — `try/catch` around the expression evaluation so malformed input fails gracefully instead of breaking the page
- **Aspect-ratio CSS** — buttons use `aspect-ratio: 1 / 1` so they stay perfectly circular at any size

## Usage

1. Download `calculator.html`
2. Open it in any modern browser
3. Click buttons or use your keyboard to build an expression
4. Press `=` or hit Enter to evaluate

No installation, no server, no dependencies.

## Possible Future Additions

- Memory functions (M+, M-, MR, MC)
- History of previous calculations
- Hyperbolic functions (`sinh`, `cosh`, `tanh`) and factorials
- A dark/light theme switch
