#ifndef DOWNLOAD_H
#define DOWNLOAD_h


#define ELAPSED_TIME(time, startTime) ((time) - (startTime))

#define PERCENT_COMPLETE(bytes, totalBytes) \
    (100.0 * (double)(bytes) / (double)(totalBytes))

#define DOWNLOAD_SPEED(time, startTime, bytes) \
    ((double)(bytes) / (double)ELAPSED_TIME(time, startTime))

#define TOTAL_TIME(time, startTime, bytes, totalBytes) \
    ((double)(totalBytes) / DOWNLOAD_SPEED(time, startTime, bytes))

#define REMAINING_TIME(time, startTime, bytes, totalBytes) \
    (TOTAL_TIME(time, startTime, bytes, totalBytes) \
    - (double)ELAPSED_TIME(time, startTime))


#endif
