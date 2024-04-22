### Part 3 Plotting: bandwidth then latency as func of message size ###
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# First we'll plot on log-log scale:
data_path = 'p3_output_w_latency.csv'
data = pd.read_csv(data_path)
print(data.columns)

# Processing col names
data.columns = data.columns.str.strip()

# Extract unique vals for message sizes and process counts
process_counts = data['Processes'].unique()
colors = plt.cm.viridis(np.linspace(0, 1, len(process_counts)))  # Color map for clear distinction

# Plotting Bandwidth on a Log-Log Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = data[data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Bandwidth (bytes/second)'], '-o', color=colors[idx], label=f'{p} Processes')
plt.xscale('log', base=2)
plt.yscale('log', base=10)
plt.xlabel('Message Size (bytes)')
plt.ylabel('Bandwidth (bytes/second)')
plt.title('Bandwidth as a Function of Message Size and Number of Processes (Log-Log Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")

# Save it:
plot_path = 'p_3_bdwdth_v_mssgsze_log_log_scale.png' 
plt.savefig(plot_path)
plt.close()

# Next let's plot bandwidth on linear scale:
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = data[data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Bandwidth (bytes/second)'], '-o', color=colors[idx], label=f'{p} Processes')
    
plt.xlabel('Message Size (bytes)')
plt.ylabel('Bandwidth (bytes/second)')
plt.title('Bandwidth as a Function of Message Size and Number of Processes (Linear Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")

# Save it:
plot_path_linear = 'p_3_bdwdth_v_mssgsze_linear_scale.png' 
plt.savefig(plot_path_linear)
plt.close()

# Next - plotting Latency as a function of message size:

# Plotting Latency on a Log-Log Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = data[data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Latency'], '-o', color=colors[idx], label=f'{p} Processes')
plt.xscale('log', base=2)
plt.yscale('log', base=10)
plt.xlabel('Message Size (bytes)')
plt.ylabel('Latency (seconds)')
plt.title('Latency as a Function of Message Size and Number of Processes (Log-Log Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")

# Save it
plot_path_latency_log_log = 'p_3_latency_v_mssgsze_log_log_scale.png'
plt.savefig(plot_path_latency_log_log)
plt.close()

# Plotting Latency on a Linear Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = data[data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Latency'], '-o', color=colors[idx], label=f'{p} Processes')
    
plt.xlabel('Message Size (bytes)')
plt.ylabel('Latency (seconds)')
plt.title('Latency as a Function of Message Size and Number of Processes (Linear Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")

# Save the latency plot on linear scale:
plot_path_latency_linear = 'p_3_latency_v_mssgsze_linear_scale.png'
plt.savefig(plot_path_latency_linear)
plt.close()

### Part 4 Plotting: bandwidth then latency as func of message size ###

data_p4_path = 'output_p4_w_latency.csv'
data_p4 = pd.read_csv(data_p4_path)
data_p4.columns = data_p4.columns.str.strip()

# First we'll plot on log-log scale:
# Aggregate data: Calculate mean bandwidth and latency for each (Message Size, Processes) combination
agg_data = data_p4.groupby(['Message Size (bytes)', 'Processes']).mean().reset_index()

# Extract unique values for message sizes and process counts
process_counts = agg_data['Processes'].unique()
colors = plt.cm.viridis(np.linspace(0, 1, len(process_counts)))  # Color map for clear distinction

# Plotting Aggregated Bandwidth on a Log-Log Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = agg_data[agg_data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Bandwidth (bytes/second)'], '-o', color=colors[idx], label=f'{p} Processes')
plt.xscale('log', base=2)
plt.yscale('log', base=10)
plt.xlabel('Message Size (bytes)')
plt.ylabel('Bandwidth (bytes/second)')
plt.title('Bandwidth as a Function of Message Size and Number of Processes (Log-Log Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.savefig('p_4_bdwdth_v_mssgsze_log_log_scale.png')
plt.close()

# Plotting Aggregated Bandwidth on a Linear Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = agg_data[agg_data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Bandwidth (bytes/second)'], '-o', color=colors[idx], label=f'{p} Processes')
plt.xlabel('Message Size (bytes)')
plt.ylabel('Bandwidth (bytes/second)')
plt.title('Bandwidth as a Function of Message Size and Number of Processes (Linear Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.savefig('p_4_bdwdth_v_mssgsze_linear_scale.png')
plt.close()

# Plotting Aggregated Latency on a Log-Log Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = agg_data[agg_data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Latency'], '-o', color=colors[idx], label=f'{p} Processes')
plt.xscale('log', base=2)
plt.yscale('log', base=10)
plt.xlabel('Message Size (bytes)')
plt.ylabel('Latency (seconds)')
plt.title('Latency as a Function of Message Size and Number of Processes (Log-Log Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.savefig('p_4_latency_v_mssgsze_log_log_scale.png')
plt.close()

# Plotting Aggregated Latency on a Linear Scale
plt.figure(figsize=(12, 8))
for idx, p in enumerate(process_counts):
    subset = agg_data[agg_data['Processes'] == p]
    plt.plot(subset['Message Size (bytes)'], subset['Latency'], '-o', color=colors[idx], label=f'{p} Processes')
plt.xlabel('Message Size (bytes)')
plt.ylabel('Latency (seconds)')
plt.title('Latency as a Function of Message Size and Number of Processes (Linear Scale)')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.savefig('p_4_latency_v_mssgsze_linear_scale.png')
plt.close()