
#!/bin/bash

mkdir -p data

echo "Generating 1 MB using Linux /dev/urandom..."

dd if=/dev/urandom of=data/linux_urandom.bin bs=1024 count=1024 status=progress

echo "Linux random data generated successfully."
echo "Generating 1 MB using OpenSSL..."

openssl rand -out data/openssl.bin 1048576

echo "OpenSSL random data generated successfully."