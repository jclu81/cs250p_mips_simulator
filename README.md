#### cs250p_mips_simulator(HW5)
#### Requirement
<span class="c10 c12">Computer Systems Architecture</span>

<span class="c12 c10">Homework 5</span>

<span class="c10 c0">MIPS Simulator</span><span class="c7 c0">
The implementation for this HW is divided into two parts:</span>

1.  <span class="c7 c0">MIPS simulator without Pipelining.</span>
2.  <span class="c7 c0">MIPS simulator with 3-stage Pipelining and Data Forwarding.</span>

<span class="c7 c0">The MIPS simulator only support the following instructions:</span>

<span class="c7 c0">add opr1, opr2, opr3          : opr1 = opr2 + opr3</span>

<span class="c7 c0">addi opr1,opr2,value    : opr1 = opr2 + value</span>

<span class="c7 c0">sub opr1, opr2, opr3          : opr1 = opr2 - opr3</span>

<span class="c7 c0">mul opr1, opr2, opr3          : opr1 = opr2 x opr3</span>

<span class="c7 c0">div opr1, opr2, opr3          : opr1 = opr2 / opr3</span>

<span class="c0">b</span> <span class="c11 c0">label</span><span class="c7 c0">                           : Branch/Jump to Label (Unconditional)</span>

<span class="c0">beq opr1, opr2,</span> <span class="c0 c11">label</span> <span class="c0">  :</span><span class="c7 c0"> Branch if Equal (opr1 == opr2) to Label</span>

<span class="c0">bnq opr1, opr2,</span> <span class="c11 c0">label</span> <span class="c7 c0">  : Branch if Not Equal (opr1 != opr2) to Label</span>

<span class="c7 c0">end                              : End of the program</span>

<span class="c0">Each opcode (instruction) has certain number of input operands. Opcode ‘end’ signals the end of the program in which case instructions in the pipeline must be completed(if applicable) and desired output must be printed. The Operands can either be registers, an immediate value or a label. MIPS processor is expected to have 8 registers ($0, $2,...,$7). Labels signifies the target instruction for the branches.</span> <span class="c4 c0">The first lien is the final results of the registers that the program should produce. The second line in the input file is the initialization values for the 8 registers (in order $0-$7).</span>

<span class="c7 c0"></span>

<span class="c0">An example input:</span>

<span class="c7 c0">2,4,6,88,67,45,44,89</span>

<span class="c0 c7">add $0,$1,$2</span>

<span class="c7 c0">label1 sub $1,$0,$4</span>

<span class="c7 c0">add $2,$3,$5</span>

<span class="c7 c0">beq $0,$7,label1</span>

<span class="c7 c0">end</span>

<span class="c7 c0"></span>

<span class="c7 c0">There is single blank between the label and the opcodes, and the opcodes and their operands. All label start with the keyword ‘label’ and followed by a numeric value.</span>

<span class="c4 c0">Pipelining and Data Forwarding Rules:</span>

<span class="c0">This is a 3 stage pipeline with Fetch, Execute and Write-Back as the only stages. Data forwarding happens ONLY after the execution of the preceding instruction to the execution stage of the current instruction. In case of Branches,</span> <span class="c0 c4">you must STALL the pipeline till the end of the execution stage for the branch to know if branch is taken or not.</span>

<span class="c7 c0"></span>

<span class="c4 c0">Output:</span>

<span class="c0">For Part 1: output at the end of the input program must be the values for all 8 registers (in order $0-$7), just like the first line of the input file.</span> <span class="c4 c0">This output should be returned as a vector<int> pointer.</span>

<span class="c0">For Part 2: when you are done with part one and your code is successfully running. Copy your solution.cpp into solution_pipeline.cpp and start implementing your pipeline. output at the end of the execution of all instructions will be the values for all 8 registers same as Part 1, the cycle of completion for</span> <span class="c0 c13">each</span><span class="c7 c0"> of the instruction in following format:</span>

<span class="c7 c0">add $3,$2,$0</span>

<span class="c7 c0"><cycle_of_completion></span>

<span class="c7 c0">For branches, the cycle of completion is the end of the execution stage. For Arithmetic instruction, completion is the end of write-back stage.</span>

<span class="c7 c0"></span>

<span class="c4 c0">Submission:</span>

<span class="c7 c0">Please clone the solution repository from :</span>

<span class="c13 c0 c16">[https://github.com/hamidre13/cs250p_mips_simulator](https://www.google.com/url?q=https://github.com/hamidre13/cs250p_mips_simulator&sa=D&ust=1512962377668000&usg=AFQjCNGQTxBW_N0m8aT0x7LjPO7r3u8iqw)</span>

<span class="c7 c0"></span>

<span class="c10 c0">All your code should be written in solution.cpp solution_pipeline.cpp file.</span> <span class="c10 c0 c17">DO NOT CHANGE THE SOLUTION CLASS SIGNATURE</span><span class="c10 c0"> otherwise we cannot run your code and YOU will receive 0.</span><span class="c7 c0">You can add functions to these classes if you want for your internal use, but do not change the default ones.</span>

<span class="c7 c0"></span>

1.  <span class="c7 c0">Make sure that your code compiles and runs on the ics lab machines.</span>
2.  <span class="c0">Generate a report with the screenshot of successful completion for each part.</span>
3.  <span class="c0 c10">When you are ready to submit your code delete all files except solution.cpp and info.txt .</span><span class="c7 c0"> write your name and student id in that file as it shows.</span>
4.  <span class="c7 c0">Put these files in a folder called studentid_studentname</span>
5.  <span class="c7 c0">ZIP the folder and submit it</span>
6.  <span class="c4 c0">There will be 10pts for correct submission</span>

<span class="c7 c0"></span>

<span class="c0">Your application must be named</span> <span class="c10 c0">‘mips’</span><span class="c7 c0"> and must take two command line input i.e. the input file with register initialization values and the instructions for the program. The second command will be clock cycle time.Also you can have a third optional command that when you provide it your app will go into debugging mode. The last command is not necessary but highly recommended.</span>

<span class="c7 c0">$./mips <input_file> clock_time debug</span>
