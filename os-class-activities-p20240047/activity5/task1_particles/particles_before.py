import threading
import random
import time

buffer = []

produced = 0
packaged = 0

BUFFER_SIZE = 100


def producer(machine_id):
    global produced

    pair_id = 0

    while True:
        pair_id += 1

        p1 = f"M{machine_id}-{pair_id}-P1"
        p2 = f"M{machine_id}-{pair_id}-P2"

        if len(buffer) >= BUFFER_SIZE:
            print("\nThe producing machine is broken")
            exit()

        # intentionally unsafe
        buffer.append(p1)

        time.sleep(random.uniform(0, 0.01))

        buffer.append(p2)

        produced += 1


def consumer():
    global packaged

    while True:

        if len(buffer) < 2:
            print("\nThe packaging machine is broken")
            exit()

        p1 = buffer.pop(0)

        time.sleep(random.uniform(0, 0.02))

        p2 = buffer.pop(0)

        pair1 = "-".join(p1.split("-")[:2])
        pair2 = "-".join(p2.split("-")[:2])

        if pair1 != pair2:
            print("\nPairs are incorrect")
            print("Packaged:", p1, "+", p2)
            exit()

        packaged += 1

        print(
            f"Produced pairs: {produced} | "
            f"Packaged pairs: {packaged} | "
            f"Buffer particles: {len(buffer)}"
        )


for i in range(3):
    threading.Thread(target=producer, args=(i + 1,), daemon=True).start()

threading.Thread(target=consumer, daemon=True).start()

while True:
    time.sleep(1)
