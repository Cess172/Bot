import discord
from discord.ext import commands
import serial
import time

# Set up intents for the bot
intents = discord.Intents.default()
intents.messages = True
intents.message_content = True  # Enable the Message Content intent

client = commands.Bot(command_prefix='/', intents=intents)

# Variable to hold the serial communication object
serialcomm = None

# Event: Bot is ready
@client.event
async def on_ready():
    print(f"We have logged in as {client.user}")

# Command to open the COM port
@client.command(name='opencom')
async def open_com(ctx):
    global serialcomm
    if serialcomm is None or not serialcomm.is_open:
        try:
            serialcomm = serial.Serial('COM4', 9600, timeout=1)  # Replace 'COM4' with your Arduino's port
            await ctx.send(f"{ctx.author.mention} COM port opened successfully!")
        except Exception as e:
            await ctx.send(f"Failed to open COM port: {e}")
    else:
        await ctx.send(f"{ctx.author.mention} COM port is already open!")

# Command to close the COM port
@client.command(name='closecom')
async def close_com(ctx):
    global serialcomm
    if serialcomm and serialcomm.is_open:
        serialcomm.close()
        serialcomm = None
        await ctx.send(f"{ctx.author.mention} COM port closed successfully!")
    else:
        await ctx.send(f"{ctx.author.mention} COM port is not open!")

# Command to send the "engage" command
@client.command(name='engage')
async def engage(ctx):
    if serialcomm and serialcomm.is_open:
        try:
            serialcomm.write("engage\n".encode())  # Send the "engage" command to Arduino
            time.sleep(0.5)  # Wait for a response
            response = serialcomm.readline().decode('utf-8').strip()
            if response:
                await ctx.send(f"Arduino responded: {response}")
            else:
                await ctx.send(f"{ctx.author.mention} Command 'engage' sent, but no response from Arduino.")
        except Exception as e:
            await ctx.send(f"Failed to send 'engage' command: {e}")
    else:
        await ctx.send(f"{ctx.author.mention} COM port is not open! Use `/opencom` to open it.")

# Run the bot with your Discord token (replace with your token)
client.run("")
