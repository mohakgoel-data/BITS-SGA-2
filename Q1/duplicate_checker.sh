
SUBMIT_DIR="./submissions"
BACKUP_DIR="./backup"
REPORT_FILE="./report.txt"
ERROR_LOG="./errors.log"
HASH_LIST="/tmp/hash_list_$$.txt"   

mkdir -p "$BACKUP_DIR" 2>>"$ERROR_LOG"
> "$REPORT_FILE"     # truncate/create report file
> "$ERROR_LOG"        # truncate/create error log
> "$HASH_LIST"

total_files=0
duplicate_files=0
backed_up_files=0

if [ ! -d "$SUBMIT_DIR" ]; then
    echo "Error: $SUBMIT_DIR does not exist." >>"$ERROR_LOG"
    exit 1
fi

for file in "$SUBMIT_DIR"/*; do
    if [ -f "$file" ]; then
        total_files=$((total_files+1))

        hash=$(md5sum "$file" 2>>"$ERROR_LOG" | awk '{print $1}')

        if [ -z "$hash" ]; then
            echo "Error: Could not read $file" >>"$ERROR_LOG"
            continue
        fi

        if grep -q "^$hash$" "$HASH_LIST" 2>>"$ERROR_LOG"; then
            duplicate_files=$((duplicate_files+1))
            echo "Duplicate found: $file" >>"$REPORT_FILE"
        else
            echo "$hash" >> "$HASH_LIST"
            cp "$file" "$BACKUP_DIR/" 2>>"$ERROR_LOG"
            backed_up_files=$((backed_up_files+1))
        fi
    fi
done

{
    echo "===== Submission Processing Report ====="
    echo "Date: $(date)"
    echo "Total files processed : $total_files"
    echo "Duplicate files found : $duplicate_files"
    echo "Unique files backed up: $backed_up_files"
    echo "=========================================="
} >> "$REPORT_FILE"

rm -f "$HASH_LIST"

echo "Processing complete. See $REPORT_FILE and $ERROR_LOG for details."