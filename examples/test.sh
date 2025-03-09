#!/bin/bash
############################################################
# Written and Copyright (c) 2025 gbamber
# Licensed under the EUPL-1.2
# SPDX-License-Identifier: EUPL-1.2
# License URL: https://joinup.ec.europa.eu/collection/eupl
# https://joinup.ec.europa.eu/collection/eupl/eupl-text-eupl-12
############################################################

# generate pad for alice and bob
echo -n "Generating pad for Alice ... "
head -c 1M /dev/urandom >./pad_alice.bin
echo -n "done. Sending pad to Bob ... "
cp ./pad_alice.bin ./pad_bob.bin
echo "done."

# generate clear text
echo -n "Generating cleartext for Alice ... "
strings -n 14 /dev/urandom | head -n 100 | sort | uniq >./clear_alice.txt
echo "done."

# alice encrypts cleartext for bob
echo -n "Alice encrypts ... "
../build/onetimepad -i ./clear_alice.txt -p ./pad_alice.bin -o cypher.txt
echo -n "done. After encrypting pads should differ ..."
diff -s pad_bob.bin pad_alice.bin

# bob decrypts cyphertext
echo -n "Bob decrypts ... "
../build/onetimepad -i cypher.txt -o clear_bob.txt -p pad_bob.bin
echo -n "done. After decrypting pads should be identical ..."
diff -s pad_bob.bin pad_alice.bin

# generate clear text answer
echo "--------------------------------------------"
echo -n "Generating cleartext for Bob ... "
strings -n 14 /dev/urandom | head -n 100 | sort | uniq >./answer_bob.txt
echo "done."

# bob encrypts answer for alice
echo -n "Bob encrypts ... "
../build/onetimepad -o cypher.txt -i ./answer_bob.txt -p ./pad_bob.bin
echo -n "done. After encrypting pads should differ ..."
diff -s pad_bob.bin pad_alice.bin

# alice decrypts answer
echo -n "Alice decrypts ... "
../build/onetimepad -i cypher.txt -o answer_alice.txt -p pad_alice.bin
echo " "

# compare original and decrypted text
echo "--------------------------------------------"
echo -n "*** Comparing cleartext ... "
diff -s clear_alice.txt clear_bob.txt
echo -n "*** Comparing answer ... "
diff -s answer_bob.txt answer_alice.txt
echo -n "*** Comparing pad ... "
diff -s pad_bob.bin pad_alice.bin

# cleanup
echo " "
echo "--------------------------------------------"
echo -n "Cleanup ..."
rm clear_alice.txt clear_bob.txt answer_alice.txt answer_bob.txt cypher.txt
echo "Done."
