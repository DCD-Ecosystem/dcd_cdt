--- kv_tests Project ---

--backing-store chainbase -- How to Build with CMake and Make --
   - cd into the 'build' directory
   - run the command 'cmake .. -DDCD_CONTRACTS_ROOT=/path/to//dcd.contracts'
   - run the command 'make'

 - After build -
   - The built smart contract is under the 'kvtest' directory in the 'build' directory
   - You can then do a 'set contract' action with 'cldcd' and point to the './build/kvtest' directory

 - Additions to CMake should be done to the CMakeLists.txt in the './src' directory and not in the top level CMakeLists.txt

 - After build -
   - The built smart contract is in the 'build' directory
   - You can then do a 'set contract' action with 'cldcd' and point to the 'build' directory
