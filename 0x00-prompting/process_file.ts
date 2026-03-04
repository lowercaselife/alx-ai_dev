import * as fs from 'fs';
import * as path from 'path';

function processLargeFile(filepath: string): string | null {
    try {
        const fileContent: string = fs.readFileSync(filepath, 'utf-8');
        console.log(`Read ${fileContent.length} characters.`);
        // Assume further processing of fileContent happens here
        return fileContent;
    } catch (error: any) {
        console.error(`Error processing file: ${error.message}`);
        return null;
    }
}

const fileToProcess = path.join(__dirname, 'very_large_data.txt');
const processedData = processLargeFile(fileToProcess);