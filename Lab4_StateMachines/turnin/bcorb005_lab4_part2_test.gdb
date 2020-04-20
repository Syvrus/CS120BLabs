# Test file for "Lab4_StateMachines"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "Test from INIT"
set state = INIT
expect state INIT
checkResult
# Add tests below
test "Test from INCREMENT"
set state = INCREMENT
expect state INCREMENT
checkResult

test "Test from DECREMENT"
set state = DECREMENT
expect state DECREMENT
checkResult

test "Test from BOTH"
set state = BOTH
expect state BOTH
checkResult

test "Test from RELEASE_I"
set state = RELEASE_I
expect state RELEASE_I
checkResult

test "Test from RELEASE_D"
set state = RELEASE_D
expect state RELEASE_D
checkResult

test "Test from RELEASE_B"
set state = RELEASE_B
expect state RELEASE_B
checkResult

test "PINA: 0x01, 0x02, 0x00 => PORTC: 0x08, 0x07, 0x00 state: INCREMENT, DECREMENT, RELEASE_B"
set state = INIT
expect state INIT
expectPORTC 0x07
setPINA 0x01
continue 1
expectPORTC 0x08
expect state INCREMENT
setPINA 0x02
continue 1
expectPORTC 0x07
continue 2
expect state DECREMENT
setPINA 0x00
continue 1
expectPORTC 0x00
expect state RELEASE_B
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
