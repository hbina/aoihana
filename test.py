#!/usr/bin/python3

from pathlib import Path
import subprocess
import os
import string
import sys
import threading

SOURCE_DIR: str = './tests'
BUILD_DIR: str = "./build"
C_COMPILER: str = "gcc"


def task(filename: Path):

    output_name = f"{Path(filename).stem}_test"
    final_output_file = f"{BUILD_DIR}/{output_name}"

    subprocess.run(args=[C_COMPILER, filename, "-g", "-o",
                         final_output_file])
    subprocess.run(args=[final_output_file])

    print(f"done testing {final_output_file}")


if __name__ == '__main__':
    Path(f"{BUILD_DIR}").mkdir(parents=True, exist_ok=True)
    tasks = []
    for dirName, subdirList, fileList in os.walk(SOURCE_DIR):
        for fname in list(filter(lambda x: x.endswith(".c"), fileList)):
            test_c_file = f"{dirName}/{fname}"
            print(f"compiling:{test_c_file}")
            thread = threading.Thread(target=task, args=(test_c_file,))
            thread.start()
            tasks.append(thread)

    for i, task in enumerate(tasks):
        task.join()
