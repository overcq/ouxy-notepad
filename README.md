# ouxy-notepad

Hierarchical notebook

# Information and instructions to the user

## 1. Contact

Manufacturer: overcq

Contact the manufacturer: overcq@int.pl

Source code: https://github.com/overcq/ouxy-notepad

Description: https://overcq.ct8.pl/ouxy-notepad.html

## 2. Vulnerabilities

Report vulnerabilities: https://github.com/overcq/ouxy-notepad/security/advisories or via e‐mail: overcq@int.pl

## 3. Version

Detailed version in git log.

## 4. Purpose

Creating and searching for notes (Unicode) organized in the structures of note trees and book trees.

## 5. Risk

You must ensure the security of the hierarchical database stored in the user's home directory in the "notepad-ocq" file and in the ".#notepad-ocq.\~number\~" backup files.

## 6. Component materials

This product uses external libraries (source code available through the operating systemʼs package system):

* “libc”
* Gtk+ 3

This product has been built using unix-like tools, in particular:

* “clang”
* GNU “make”
* “pkg-config”
* “scons” (dependence on Python)
* shell

## 7. EU declaration

No the EU declaration of conformity.

## 8. Support

Technical security support via e‐mail: overcq@int.pl

Issues at: https://github.com/overcq/ouxy-notepad/issues

Product support continues for the latest git release.

## 9. Installation and update

Fetching for first use can be done with a command, for example `git clone git@github.com:overcq/ouxy-notepad.git`.

The user should make regular updates, e.g. with a command `git pull && make`.
Before using this commands can be executed: `make clean`, to remove any remaining intermediate files that depend on source files that have been removed in the new product version.

To completely remove the product from the userʼs device, execute, for example: `rm -fr binary-change`.
