Explanations
mkdir submissions + echo — Created sample submission files, with s2.py as a duplicate of s1.py to test the script.
chmod +x — Gave the script execute permission so it can run directly.
./duplicate_checker.sh — Ran the script; it hashed each file, skipped duplicates, and copied unique files to backup.
cat report.txt — Showed the summary: total files, duplicates found, files backed up.
cat errors.log — Confirmed no errors occurred during execution.
ls backup/ — Verified only unique files (s1.py, s3.py) were backed up.

Justification
md5sum: compares file content, not names, so renamed duplicates are still caught.
>: used once to reset report/log files at the start of each run.
>>: used to append results progressively without overwriting.
2>>: redirects only error messages to errors.log, keeping them separate from the report.
mkdir -p: avoids errors if the backup folder already exists.
[ -f ]: ensures only files (not folders) are processed.