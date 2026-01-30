# FREE Attack Vector Demonstration

> **Purpose & Scope**  
> This repository is **only** intended to **demonstrate the validity and experimental reproducibility** of the **FREE attack vector** in a **local microVM-based containers environment**.  
> It is provided for **research evaluation** purposes **only**.

## ⚠️ Responsible Use

- **Do not** use this repository to target systems you do not own or do not have explicit permission to test.
- The materials here are intentionally limited to reduce misuse risk:
  - No weaponized automation against real targets
  - No target lists or “ready-to-deploy” exploit pipelines

If you believe any part of this repository could be abused, please contact us (see **Contact**).

---

## What this repo contains

- **Key steps** to set up the experimental environment
- **Minimal reproduction code** to validate the FREE attack vector in a lab setting
- **Relevant configurations** used in our evaluation
- **Screenshots** and logs demonstrating expected outcomes

---

## Requirements (high level)

Because Kata Containers depends on virtualization, you will typically need:

- A Linux host with **hardware virtualization** support (VT-x / AMD-V)
- MicroVM-based containers with Kubernetes, which are built based on the following official documents:
  - [kata-containers/docs/Developer-Guide.md at main · kata-containers/kata-containers · GitHub](https://github.com/kata-containers/kata-containers/blob/main/docs/Developer-Guide.md)
  - [kata-containers/docs/how-to/how-to-use-k8s-with-containerd-and-kata.md at main · kata-containers/kata-containers · GitHub](https://github.com/kata-containers/kata-containers/blob/main/docs/how-to/how-to-use-k8s-with-containerd-and-kata.md)
  - [kata-containers/docs/how-to/how-to-use-kata-containers-with-firecracker.md at main · kata-containers/kata-containers](https://github.com/kata-containers/kata-containers/blob/main/docs/how-to/how-to-use-kata-containers-with-firecracker.md)

- (Optional) **Nested virtualization** if running inside a VM

---

## Quick Start

1. **A simple PoC of attack vector of FREE**

   Compile the following code `FREE_test.c`, then install it into your container image for testing.

   ```bash
   gcc FREE_test.c -o FREE_test -static
   ```

2. **The yaml file for deploying container Pod** can refer to `busybox-dep.yaml`:

   ```bash
   kubectl apply -f busybox-dep.yaml
   ```

3. **Run the `FREE_test` program in the container**, here are the screenshots of a local test:

   Initial host memory disk usage：

   <img src=".\screenshots\image-20260130141908356.png" alt="image-20260130141908356" style="zoom: 25%;" />

   After running the test program：

   <img src=".\screenshots\image-20260130142231391.png" alt="image-20260130142231391" style="zoom:25%;" />

The container is actually over-consuming the host machine's memory and storage resources, but it hasn't triggered an OOM-kill or pod eviction.

## Screenshots of Communications With Relevant Cloud Security Teams

1. Online meeting with Alibaba security teams Guanxing (The topic name has been translated into English):

   At the meeting, their security engineers **acknowledged the security issues revealed by FREE** and are discussing mitigations for FREE.

   <img src=".\screenshots\image-20260130151957125.png" alt="image-20260130151957125" style="zoom: 80%;" />

2. With AWS Security

   <img src=".\screenshots\image-20260130151217277.png" alt="image-20260130151217277" style="zoom: 50%;" />

3. With Azure Security

   <img src=".\screenshots\image-20260130151528700.png" alt="image-20260130151528700" style="zoom:50%;" />