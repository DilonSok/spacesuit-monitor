1. Install System Dependencies
Run the following:

sudo apt update
sudo apt install -y \
    git \
    cmake \
    ninja-build \
    gperf \
    ccache \
    dfu-util \
    device-tree-compiler \
    wget \
    xz-utils \
    file \
    make \
    gcc \
    g++ \
    python3 \
    python3-pip \
    python3-venv \
    qemu-system-x86

2. Install West (Zephyr Meta Tool)
Create a Python virtual environment:

mkdir -p ~/zephyr-tools
cd ~/zephyr-tools
python3 -m venv .venv
source .venv/bin/activate
pip install --upgrade pip
pip install west

Important: Every new terminal session must activate the environment:

source ~/zephyr-tools/.venv/bin/activate

3. Create Zephyr Workspace
The workspace will be created at:

~/zephyrproject

Initialize Zephyr:

cd ~
mkdir zephyrproject
cd zephyrproject
west init -m https://github.com/zephyrproject-rtos/zephyr --mr main
west update
west zephyr-export

Install Zephyr Python requirements:

pip install -r zephyr/scripts/requirements.txt

4. Install Zephyr SDK
From inside ~/zephyrproject:

wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.4/zephyr-sdk-0.17.4_linux-x86_64.tar.xz
tar -xf zephyr-sdk-0.17.4_linux-x86_64.tar.xz
cd zephyr-sdk-0.17.4
./setup.sh

During setup:

Install host tools → Yes
Register CMake package → Yes

Set the SDK path permanently:

echo 'export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyrproject/zephyr-sdk-0.17.4' >> ~/.bashrc
source ~/.bashrc

Verify:

echo $ZEPHYR_SDK_INSTALL_DIR

5. Clone the Spacesuit Monitor Application

Create the apps directory:

cd ~/zephyrproject
mkdir apps
cd apps

Clone the repository:

git clone https://github.com/DilonSok/spacesuit-monitor.git spacesuit_monitor
cd spacesuit_monitor

6. Build the Application

From inside:
~/zephyrproject/apps/spacesuit_monitor

Run:
west build -b qemu_x86 -p always

7. Run the Application
west build -t run