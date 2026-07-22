Swap files
vi automatically creates a hidden swap file (.filename.swp) in the same directory as soon as editing begins. It periodically saves buffer changes to this file. After a crash, running vi -r filename reconstructs the file from the swap file, recovering almost all unsaved changes. This is the primary and most complete recovery mechanism vi provides for a crash scenario.

Undo history
Undo history (accessed with u) exists only in vi's memory during an active session. It is not written to disk, so once the process is killed by a crash, the undo history is lost entirely. It is useful for correcting mistakes during editing but offers no protection against a crash.

Registers
Registers store copied or deleted text temporarily for pasting within the same session. Like undo history, registers exist only in memory and vanish when the process terminates unexpectedly, so they cannot help recover a file after a crash.

Backup files
If backup options are enabled, vi/vim can keep a backup copy (filename~) of the file as it existed at the last save. This protects against a bad save overwriting good data, but it does not include any changes made after the last save, so it does not recover the specific work lost in a crash.

Auto-recovery
This refers to vi's own crash-detection behavior: when reopening a file that has a leftover swap file, vi warns the user that a swap file exists and offers to recover. This is really the swap file mechanism being triggered automatically, not a separate feature.

Most Reliable Recovery Strategy

The swap file mechanism is the most reliable recovery strategy after a crash, because it is the only mechanism that persists changes to disk continuously during editing, independent of whether the file was ever saved. Undo history and registers are memory-only and are lost the moment the process dies, and backup files only reflect the last saved state, missing any unsaved work. Using vi -r filename immediately after a crash, before opening the file normally again, gives the best chance of recovering the most recent unsaved changes, since opening it normally first can prompt vi to treat the old swap file as stale.