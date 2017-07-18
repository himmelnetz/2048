<?php

# this view generator is very hacky and does things like dump jquery in every html, but it
# allows for htmls to be self-contained

assert($argc == 2, "need to provide trace file on command line");

$NUM_ROWS = 4;
$NUM_COLS = 4;

$JQUERY_PATH = "jquery-2.1.4.min.js";
$JQUERY_UI_PATH = "jquery-ui.js";
$JQUERY_UI_CSS_PATH = "jquery-ui-smoothness.css";
$CSS_RESET_PATH = "reset.css";

$filename = $argv[1];
$trace_json = file_get_contents($filename);

?>

<!DOCTYPE html>
<html>
<head>
    <title>Trace Viewer</title>
    <style type="text/css">
<?php echo file_get_contents($CSS_RESET_PATH); ?>
    </style>
    <style type="text/css">
<?php echo file_get_contents($JQUERY_UI_CSS_PATH); ?>
    </style>
    <style type="text/css">

.board-2048 {
    outline: 8px solid black;
    margin: 16px;
}

td {
    width: 100px;
    height: 100px;
    text-align: center;
    vertical-align: middle;
    outline: 4px solid black;
    font-family: "Helvetica Neue", Arial, sans-serif;
    font-weight: bold;
    font-size: 55px;
    color: #776E65;
}

.cell-value-0 {
    background: #eee4da;
    color: #eee4da;
}
.cell-value-2 {
    background: #eee4da;
}
.cell-value-4 {
    background: #ede0c8;
}
.cell-value-8 {
    color: #f9f6f2;
    background: #f2b179;
}
.cell-value-16 {
    color: #f9f6f2;
    background: #f59563;
}
.cell-value-32 {
    color: #f9f6f2;
    background: #f67c5f;
}
.cell-value-64 {
    color: #f9f6f2;
    background: #f65e3b;
}
.cell-value-128 {
    color: #f9f6f2;
    background: #edcf72;
    font-size: 45px;
}
.cell-value-256 {
    color: #f9f6f2;
    background: #edcc61;
    font-size: 45px;
}
.cell-value-512 {
    color: #f9f6f2;
    background: #edc850;
    font-size: 45px;
}
.cell-value-1024 {
    color: #f9f6f2;
    background: #edc53f;
    font-size: 35px;
}
.cell-value-2048 {
    color: #f9f6f2;
    background: #edc22e;
    font-size: 35px;
}
.cell-value-super {
    color: #f9f6f2;
    background: #3c3a32;
    font-size: 30px;
}

.score-box {
    margin: 16px;
    font-family: "Helvetica Neue", Arial, sans-serif;
    font-weight: bold;
    font-size: 32px;
}

#state-slider {
    width: 400px;
    margin: 16px;
}

    </style>
    <script>
<?php echo file_get_contents($JQUERY_PATH); ?>
    </script>
    <script>
<?php echo file_get_contents($JQUERY_UI_PATH); ?>
    </script>
    <script>
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

var trace = JSON.parse('<?php echo $trace_json; ?>');
var NUM_ROWS = trace.num_rows;
var NUM_COLS = trace.num_cols;

var LEFT_KEY_KEYCODE = 37;
var RIGHT_KEY_KEYCODE = 39;

function set_to_state(stateI, change_slider) {
    var state = trace.states[stateI];
    for (var row = 0; row < NUM_ROWS; row++) {
        for (var col = 0; col < NUM_COLS; col++) {
            var value = state.board[row][col];
            $("#cell-" + row + "-" + col)
                .text(state.board[row][col])
                .removeClass()
                .addClass(value > 2048
                    ? "cell-value-super"
                    : "cell-value-" + value);
        }
    }
    $("#score-number").text(state.score);
    if (change_slider) {
        $("#state-slider").slider({
            value: stateI
        });
    }
}

function on_slider_change() {
    var stateI = $("#state-slider").slider("value");
    set_to_state(stateI, false);
}

function init_slider() {
    $("#state-slider").slider({
        max: trace.states.length - 1,
        slide: on_slider_change,
        change: on_slider_change
    });
}

$(document).ready(function() {
    init_slider();
    set_to_state(0);
});

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
    </script>
</head>
<body>
    <table class="board-2048">
        <?php for ($row = 0; $row < $NUM_ROWS; $row++) {?><tr>
            <?php for ($col = 0; $col < $NUM_COLS; $col++) {?><td id="<?php echo "cell-" . $row . "-" . $col; ?>"></td>
            <?php } ?>
        </tr>
        <?php } ?>
    </table>
    <div class="score-box">Score: <span id="score-number"></span></div>
    <div id="state-slider"></div>
</body>
</html>
