<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Scientific Calculator</title>
    <style>
        * {
            box-sizing: border-box;
        }

        body {
            margin: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            background-color: hsl(0, 0%, 95%);
            font-family: Arial, sans-serif;
            padding: 16px;
        }

        #calculator {
            background-color: hsl(0, 0%, 15%);
            border-radius: 15px;
            width: min(420px, 100%);
            padding-bottom: clamp(12px, 3vw, 20px);
            overflow: hidden;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.3);
        }

    
        #mode-strip {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: clamp(8px, 2vw, 10px) clamp(14px, 4vw, 20px) 0;
            color: hsl(0, 0%, 55%);
            font-size: clamp(0.7rem, 2.5vw, 0.9rem);
            gap: 8px;
        }

        #mode-strip .toggle-group {
            display: flex;
            gap: 6px;
        }

        #mode-strip button {
            width: auto;
            height: auto;
            aspect-ratio: unset;
            padding: 5px 10px;
            border-radius: 20px;
            font-size: clamp(0.65rem, 2.3vw, 0.85rem);
            background-color: hsl(0, 0%, 25%);
        }

        #mode-strip button.active {
            background-color: hsl(35, 100%, 55%);
            color: hsl(0, 0%, 10%);
        }

        #display-wrap {
            padding: clamp(8px, 2vw, 10px) clamp(14px, 4vw, 20px) clamp(12px, 3vw, 20px);
        }

        #expression {
            width: 100%;
            min-height: 18px;
            color: hsl(0, 0%, 55%);
            font-size: clamp(0.85rem, 3vw, 1.1rem);
            text-align: right;
            overflow-x: auto;
            white-space: nowrap;
        }

        #display {
            width: 100%;
            padding: 5px 0;
            font-size: clamp(1.8rem, 8vw, 2.6rem);
            text-align: right;
            border: none;
            background-color: transparent;
            color: white;
            font-family: inherit;
        }

        #keys {
            display: grid;
            grid-template-columns: repeat(5, 1fr);
            gap: clamp(6px, 2vw, 10px);
            padding: 0 clamp(14px, 4vw, 20px);
        }

        button {
            width: 100%;
            aspect-ratio: 1 / 1;
            border-radius: 50%;
            border: none;
            background-color: hsl(0, 0%, 30%);
            color: white;
            font-size: clamp(0.85rem, 3.5vw, 1.35rem);
            font-weight: bold;
            cursor: pointer;
            transition: background-color 0.1s ease;
        }

        button:hover {
            background-color: hsl(0, 0%, 40%);
        }

        button:active {
            background-color: hsl(0, 0%, 50%);
        }

        
        .operator-btn {
            background-color: hsl(35, 100%, 55%);
        }

        .operator-btn:hover {
            background-color: hsl(35, 100%, 65%);
        }

        .operator-btn:active {
            background-color: hsl(35, 100%, 75%);
        }

        
        .fn-btn {
            background-color: hsl(0, 0%, 22%);
            font-size: clamp(0.7rem, 3vw, 1.05rem);
        }

        .fn-btn:hover {
            background-color: hsl(0, 0%, 32%);
        }

        .fn-btn.active {
            background-color: hsl(35, 100%, 55%);
            color: hsl(0, 0%, 10%);
        }

        .equals-btn {
            background-color: hsl(150, 55%, 40%);
            border-radius: 40px;
            aspect-ratio: unset;
            height: clamp(46px, 12vw, 60px);
            font-size: clamp(1.1rem, 4vw, 1.5rem);
        }

        .equals-btn:hover {
            background-color: hsl(150, 55%, 48%);
        }

        .equals-btn:active {
            background-color: hsl(150, 55%, 55%);
        }

        .wide {
            grid-column: span 2;
            border-radius: 40px;
            aspect-ratio: unset;
            height: clamp(46px, 12vw, 60px);
        }

        .full-row {
            grid-column: span 5;
        }

        #error-flash {
            color: hsl(0, 70%, 55%);
            text-align: right;
            font-size: clamp(0.65rem, 2.3vw, 0.8rem);
            min-height: 16px;
            padding: 0 clamp(14px, 4vw, 20px);
        }

        
        @media (max-width: 360px) {
            #keys {
                gap: 5px;
            }

            button {
                font-size: 0.8rem;
            }
        }
    </style>
</head>
<body>

    <div id="calculator">

        <div id="mode-strip">
            <span>Scientific Mode</span>
            <div class="toggle-group">
                <button id="deg-btn" class="active" onclick="setAngleMode('deg')">DEG</button>
                <button id="rad-btn" onclick="setAngleMode('rad')">RAD</button>
            </div>
        </div>

        <div id="display-wrap">
            <div id="expression"></div>
            <input id="display" readonly value="0">
        </div>
        <div id="error-flash"></div>

        <div id="keys">
            
            <button class="fn-btn" id="inv-btn" onclick="toggleInverse()">2nd</button>
            <button class="fn-btn" id="sin-btn" onclick="appendFunction('sin')">sin</button>
            <button class="fn-btn" id="cos-btn" onclick="appendFunction('cos')">cos</button>
            <button class="fn-btn" id="tan-btn" onclick="appendFunction('tan')">tan</button>
            <button class="operator-btn" onclick="deleteLast()">DEL</button>

            
            <button class="fn-btn" onclick="appendToDisplay('sqr(')">x&sup2;</button>
            <button class="fn-btn" onclick="appendToDisplay('recip(')">1/x</button>
            <button class="fn-btn" onclick="appendToDisplay('sqrt(')">&radic;x</button>
            <button class="fn-btn" onclick="appendToDisplay('log(')">log</button>
            <button class="fn-btn" onclick="appendToDisplay('ln(')">ln</button>

            
            <button class="fn-btn" onclick="appendToDisplay('(')">(</button>
            <button class="fn-btn" onclick="appendToDisplay(')')">)</button>
            <button class="fn-btn" onclick="appendToDisplay('%')">%</button>
            <button class="fn-btn" onclick="insertConstant('PI')">&pi;</button>
            <button class="fn-btn" onclick="insertConstant('E')">e</button>

            
            <button onclick="appendToDisplay('7')">7</button>
            <button onclick="appendToDisplay('8')">8</button>
            <button onclick="appendToDisplay('9')">9</button>
            <button class="operator-btn" onclick="appendToDisplay('/')">/</button>
            <button class="operator-btn" onclick="clearDisplay()">C</button>

            
            <button onclick="appendToDisplay('4')">4</button>
            <button onclick="appendToDisplay('5')">5</button>
            <button onclick="appendToDisplay('6')">6</button>
            <button class="operator-btn" onclick="appendToDisplay('*')">*</button>
            <button class="fn-btn" onclick="insertAnswer()">ANS</button>

            
            <button onclick="appendToDisplay('1')">1</button>
            <button onclick="appendToDisplay('2')">2</button>
            <button onclick="appendToDisplay('3')">3</button>
            <button class="operator-btn" onclick="appendToDisplay('-')">-</button>
            <button class="fn-btn" onclick="toggleSign()">+/-</button>

            
            <button class="wide" onclick="appendToDisplay('0')">0</button>
            <button onclick="appendToDisplay('.')">.</button>
            <button class="fn-btn" onclick="appendToDisplay('^')">x^y</button>
            <button class="operator-btn" onclick="appendToDisplay('+')">+</button>

            
            <button class="equals-btn full-row" onclick="calculate()">=</button>
        </div>
    </div>

    <script>
        

        let expression = '';
        let angleMode = 'deg';   
        let inverseMode = false; 
        let lastAnswer = 0;
        let justCalculated = false;

        const displayEl = document.getElementById('display');
        const expressionEl = document.getElementById('expression');
        const errorEl = document.getElementById('error-flash');

        function setAngleMode(mode) {
            angleMode = mode;
            document.getElementById('deg-btn').classList.toggle('active', mode === 'deg');
            document.getElementById('rad-btn').classList.toggle('active', mode === 'rad');
        }

        function toggleInverse() {
            inverseMode = !inverseMode;
            document.getElementById('inv-btn').classList.toggle('active', inverseMode);
            document.getElementById('sin-btn').textContent = inverseMode ? 'sin⁻¹' : 'sin';
            document.getElementById('cos-btn').textContent = inverseMode ? 'cos⁻¹' : 'cos';
            document.getElementById('tan-btn').textContent = inverseMode ? 'tan⁻¹' : 'tan';
        }

        function appendFunction(name) {
            const token = inverseMode ? 'a' + name : name;
            appendToDisplay(token + '(');
        }

        function appendToDisplay(value) {
            
            if (justCalculated) {
                const startsNewExpression = /[0-9(]/.test(value) || /^[a-z]/.test(value);
                expression = startsNewExpression ? '' : expression;
                justCalculated = false;
            }

            expression += value;
            render();
        }

        function insertConstant(name) {
            if (justCalculated) {
                expression = '';
                justCalculated = false;
            }
            expression += name;
            render();
        }

        function insertAnswer() {
            if (justCalculated) {
                expression = '';
                justCalculated = false;
            }
            expression += 'ANS';
            render();
        }

        function toggleSign() {
            if (expression === '') return;
            if (expression.startsWith('-(') && expression.endsWith(')')) {
                expression = expression.slice(2, -1);
            } else {
                expression = '-(' + expression + ')';
            }
            justCalculated = false;
            render();
        }

        function deleteLast() {
            expression = expression.slice(0, -1);
            justCalculated = false;
            render();
        }

        function clearDisplay() {
            expression = '';
            justCalculated = false;
            clearError();
            render();
        }

        function render() {
            expressionEl.textContent = expression;
            displayEl.value = expression === '' ? '0' : expression;
        }

        function clearError() {
            errorEl.textContent = '';
        }

        function showError(message) {
            errorEl.textContent = message;
        }

        
        function toRadians(x) {
            return angleMode === 'deg' ? (x * Math.PI) / 180 : x;
        }

        function fromRadians(x) {
            return angleMode === 'deg' ? (x * 180) / Math.PI : x;
        }

        function sin(x) { return Math.sin(toRadians(x)); }
        function cos(x) { return Math.cos(toRadians(x)); }
        function tan(x) { return Math.tan(toRadians(x)); }
        function asin(x) { return fromRadians(Math.asin(x)); }
        function acos(x) { return fromRadians(Math.acos(x)); }
        function atan(x) { return fromRadians(Math.atan(x)); }
        function log(x) { return Math.log10(x); }
        function ln(x) { return Math.log(x); }
        function sqrt(x) { return Math.sqrt(x); }
        function sqr(x) { return x * x; }
        function recip(x) { return 1 / x; }

        function calculate() {
            if (expression.trim() === '') {
                return;
            }

            clearError();

            
            const opens = (expression.match(/\(/g) || []).length;
            const closes = (expression.match(/\)/g) || []).length;
            const balanced = expression + ')'.repeat(Math.max(0, opens - closes));

            
            const safeExpression = balanced
                .replace(/\^/g, '**')
                .replace(/%/g, '/100');

            try {
                
                const result = Function(
                    'sin', 'cos', 'tan', 'asin', 'acos', 'atan',
                    'log', 'ln', 'sqrt', 'sqr', 'recip', 'PI', 'E', 'ANS',
                    `"use strict"; return (${safeExpression});`
                )(sin, cos, tan, asin, acos, atan, log, ln, sqrt, sqr, recip, Math.PI, Math.E, lastAnswer);

                if (typeof result !== 'number' || !isFinite(result)) {
                    throw new Error('Invalid result');
                }


                const rounded = Math.round(result * 1e10) / 1e10;

                lastAnswer = rounded;
                expression = String(rounded);
                justCalculated = true;
                render();
            } catch (err) {
                showError('Error: check your expression');
            }
        }

        document.addEventListener('keydown', (e) => {
            const key = e.key;

            if (/[0-9.+\-*/()%^]/.test(key)) {
                appendToDisplay(key);
            } else if (key === 'Enter' || key === '=') {
                e.preventDefault();
                calculate();
            } else if (key === 'Backspace') {
                deleteLast();
            } else if (key === 'Escape') {
                clearDisplay();
            }
        });
    </script>
</body>
</html>
