import subprocess
import random
import re
import sys

# --- Configuration ---
NUM_RUNS = 10  # Set to 10 for testing, change to 50 later
TEST_LIST = [
    "fill_drain_test", 
    "concurrent_rw_test", 
    "overflow_underflow_test", 
    "random_test", 
    "reset_stress_test"
]

# The base command from your Makefile
CMD_BASE = ["./obj_dir/Vtop"]

# --- Coverage Target Dictionary ---
# Keys perfectly match the text printed by functional_coverage.cpp
coverage_bins = {
    "Empty"                      : 0,
    "Near Empty"                 : 0,
    "Mid Range"                  : 0,
    "Near Full"                  : 0,
    "Full"                       : 0,
    "Write when Full (Overflow)" : 0,
    "Read when Empty (Underflow)": 0,
    "Simultaneous RW (Empty)"    : 0,
    "Simultaneous RW (Mid)"      : 0,
    "Simultaneous RW (Full)"     : 0,
    "Reset at Full Capacity"     : 0,
    "Reset at Empty Capacity"    : 0
}

print("======================================================")
print(f"  STARTING UVM REGRESSION SUITE ({NUM_RUNS} LOOPS)")
print("======================================================")

total_tests_run = 0
passed_tests = 0

# 1. Outer Loop: Run the entire suite NUM_RUNS times
for i in range(1, NUM_RUNS + 1):
    # Generate a random seed for Verilator & SystemVerilog
    current_seed = random.randint(1, 999999999)
    print(f"\n[LOOP {i}/{NUM_RUNS}] Using Master Seed: {current_seed}")
    
    # 2. Inner Loop: Run every test in the verification plan
    for test in TEST_LIST:
        total_tests_run += 1
        
        # Build the command: ./obj_dir/Vtop +UVM_TESTNAME=... +verilator+seed=...
        run_cmd = CMD_BASE + [f"+TESTNAME={test}", f"+verilator+seed+{current_seed}"]
        
        # Execute silently and capture output
        result = subprocess.run(run_cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        output = result.stdout

        # Check for UVM Fatal/Error (Basic Pass/Fail tracking)
        if "UVM_FATAL :" in output and " 0" not in output.split("UVM_FATAL :")[1][:5]:
            print(f"  -> {test:<25} \033[91m[FAIL]\033[0m")
        else:
            print(f"  -> {test:<25} \033[92m[PASS]\033[0m")
            passed_tests += 1

        # 3. Parse Coverage Data via Regex
        for key in coverage_bins.keys():
            # Looks for exactly: "  Key Name  : 5" and extracts the 5
            safe_key = re.escape(key)
            match = re.search(fr"{safe_key}\s*:\s*(\d+)", output)
            if match:
                # Add the hits from this specific test to the global total
                coverage_bins[key] += int(match.group(1))

# --- Calculate Final Percentage ---
total_bins = len(coverage_bins)
hit_bins = sum(1 for hits in coverage_bins.values() if hits > 0)
coverage_percentage = (hit_bins / total_bins) * 100

print("\n======================================================")
print("             CUMULATIVE COVERAGE SUMMARY              ")
print("======================================================")
print(f" Total Tests Executed : {total_tests_run}")
print(f" Passing Tests        : {passed_tests}/{total_tests_run}")
print("------------------------------------------------------")

# Print the aggregated hits for each bin
for key, hits in coverage_bins.items():
    if hits > 0:
        print(f" \033[92m[HIT]\033[0m {key:<30} : {hits} hits")
    else:
        print(f" \033[91m[MIS]\033[0m {key:<30} : 0 hits")

print("======================================================")
# Color code the final percentage
if coverage_percentage == 100.0:
    print(f" FINAL FUNCTIONAL COVERAGE: \033[92m{coverage_percentage:.1f}%\033[0m")
else:
    print(f" FINAL FUNCTIONAL COVERAGE: \033[93m{coverage_percentage:.1f}%\033[0m")
print("======================================================\n")