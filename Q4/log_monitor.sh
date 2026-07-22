LOG_FILE="server.log"
ERROR_REPORT="error_report.txt"

touch "$LOG_FILE"
touch "$ERROR_REPORT"

tail -f "$LOG_FILE" 2>/dev/null | grep --line-buffered "ERROR" | tee -a "$ERROR_REPORT" > /dev/null