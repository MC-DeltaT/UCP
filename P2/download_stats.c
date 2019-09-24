#include "download_stats.h"


int elapsedTime(long time, long startTime)
{
    return time - startTime;
}


double percentComplete(long bytes, long totalBytes)
{
    return 100.0 * (double)bytes / (double)totalBytes;
}


double downloadSpeed(long time, long startTime, long bytes)
{
    return (double)bytes / (double)elapsedTime(time, startTime);
}


double totalTime(long time, long startTime, long bytes, long totalBytes)
{
    return (double)totalBytes / downloadSpeed(time, startTime, bytes);
}


double remainingTime(long time, long startTime, long bytes, long totalBytes)
{
    return totalTime(time, startTime, bytes, totalBytes)
            - (double)elapsedTime(time, startTime);
}
