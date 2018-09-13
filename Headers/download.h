#pragma once

typedef struct Download_Request
{
    char filename[50];
    int C_RNTI;
} Download_Request;

typedef struct Download_Info
{
    char filename[50];
    int download_id;
    int number_of_packets;
} Download_Info;

typedef struct Download_Packet
{
    
} Download_Packet;