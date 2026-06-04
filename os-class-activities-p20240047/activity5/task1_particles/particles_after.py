import threading
import time
import random

buffer = []

BUFFER_PAIRS = 50

produced = 0
packaged = 0

empty_pairs = threading.Semaphore(BUFFER_PAIRS)
full_pairs = threading.Semaphore(0)

mutex = threading.Semaphore(1)


def producer(machine_id):
    global produced

    pair_id = 0

    while True:

        pair_id += 1

        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"

        empty_pairs.acquire()

        mutex.acquire()

        buffer.append(p1)
        buffer.append(p2)

        produced += 1

        mutex.release()

        full_pairs.release()

        time.sleep(random.uniform(0.01, 0.05))


def consumer():
    global packaged

    while True:

        full_pairs.acquire()

        mutex.acquire()

        if len(buffer) < 2:
            print("\nThe packaging machine is broken")
            exit()

        p1 = buffer.pop(0)
        p2 = buffer.pop(0)

        pair1 = "-".join(p1.split("-")[:2])
        pair2 = "-".join(p2.split("-")[:2])

        if pair1 != pair2:
            print("\nPairs are incorrect")
            exit()

        packaged += 1

        print(
            f"Produced pairs: {produced} | "
            f"Packaged pairs: {packaged} | "
            f"Buffer particles: {len(buffer)}"
        )

        mutex.release()

        empty_pairs.release()

        time.sleep(random.uniform(0.01, 0.05))


for i in range(3):
    threading.Thread(target=producer, args=(i + 1,), daemon=True).start()

threading.Thread(target=consumer, daemon=True).start()

while True:
    time.sleep(1)
