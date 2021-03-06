
int shell_main(int argc, char **argv);

typedef struct sqlite3_wal_replication_frame {
  void *pBuf;        /* Page content of the WAL frame to be written */
  unsigned pgno;     /* Page number */
  unsigned iPrev;    /* Most recent frame also containing pgno, or 0 if new */
} sqlite3_wal_replication_frame;

typedef struct sqlite3_wal_replication sqlite3_wal_replication;
typedef struct sqlite3_wal_replication {
  int iVersion;                   /* Structure version number (currently 1) */
  sqlite3_wal_replication *pNext; /* Next registered WAL sync implementation */
  const char *zName;              /* Name of this replication implementation */
  void *pAppData;                 /* Pointer to application-specific data */
  int (*xBegin)(sqlite3_wal_replication*, void *pArg);
  int (*xAbort)(sqlite3_wal_replication*, void *pArg);
  int (*xFrames)(sqlite3_wal_replication*, void *pArg, int szPage, int nFrame,
      sqlite3_wal_replication_frame *aFrame, unsigned nTruncate, int isCommit);
  int (*xUndo)(sqlite3_wal_replication*, void *pArg);
  int (*xEnd)(sqlite3_wal_replication*, void *pArg);
} sqlite3_wal_replication;
