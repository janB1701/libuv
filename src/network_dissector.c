#include <stdio.h>
#include <stdint.h>
#include <string.h>


struct ether_header {
    uint8_t ether_destination[6];
    uint8_t ether_source[6];
    uint16_t ether_type;
};

struct ip_header {
    uint8_t ip_vhl;
    uint8_t ip_tos;
    uint16_t ip_len;
    uint16_t ip_id;
    uint16_t ip_off;
    uint8_t ip_ttl;
    uint8_t ip_prot;
    uint16_t ip_sum;
    uint32_t ip_src;
    uint32_t ip_dst;
};

int main()
{
    uint8_t packet_bytes[] = {
        0x00, 0x13, 0x3b, 0x0c, 0x80, 0x0b, 0x00, 0x90,
        0x4c, 0x2c, 0x30, 0x02, 0x08, 0x00, 0x45, 0x00,
        0x00, 0x51, 0xdc, 0xd6, 0x40, 0x00, 0x40, 0x06,
        0xd9, 0xc4, 0xc0, 0xa8, 0x01, 0x01, 0xc0, 0xa8,
        0x01, 0xba, 0x13, 0xae, 0xc2, 0xca, 0x7e, 0x02,
        0xe0, 0xd3, 0xff, 0x3a, 0x15, 0x07, 0x80, 0x18,
        0x01, 0xc5, 0x38, 0x89, 0x00, 0x00, 0x01, 0x01,
        0x08, 0x0a, 0x00, 0x00, 0x3c, 0x05, 0x3e, 0x7c,
        0x34, 0xed, 0x41, 0x73, 0x74, 0x65, 0x72, 0x69,
        0x73, 0x6b, 0x20, 0x43, 0x61, 0x6c, 0x6c, 0x20,
        0x4d, 0x61, 0x6e, 0x61, 0x67, 0x65, 0x72, 0x2f,
        0x35, 0x2e, 0x30, 0x2e, 0x31, 0x0d, 0x0a
    };
    struct ether_header *eth_header = (struct ether_header*) packet_bytes;
    printf("Ethernet destination MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n", 
            eth_header->ether_destination[0], eth_header->ether_destination[1], eth_header->ether_destination[2], 
            eth_header->ether_destination[3], eth_header->ether_destination[4], eth_header->ether_destination[5]);
    printf("Ethernet source MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n", 
            eth_header->ether_source[0], eth_header->ether_source[1], eth_header->ether_source[2], 
            eth_header->ether_source[3], eth_header->ether_source[4], eth_header->ether_source[5]);

    printf ("--------------------------------------------------\n");
    //printf ("EtherType: 0x%04x\n", (packet_bytes[12] << 8) | packet_bytes[13]);

    struct ip_header head;
    memcpy (&head, packet_bytes + 14, sizeof(struct ip_header));
    // uint32_t dst = (head.ip_dst >> 24) | ((head.ip_dst & 0x00ff0000) >> 8) |
    //                       ((head.ip_dst & 0x0000ff00) << 8) | (head.ip_dst << 24);

    uint32_t ip_addr = head.ip_src;
    uint8_t* octets = (uint8_t*) &ip_addr;
    printf("IP source: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);

    ip_addr = head.ip_dst;
    octets = (uint8_t*) &ip_addr;
    printf("IP destination: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);
    return 0;
}