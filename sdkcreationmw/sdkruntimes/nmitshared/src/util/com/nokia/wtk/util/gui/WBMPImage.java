/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/
/*
 * $Id: WBMPImage.java,v 1.4 2005/08/26 22:45:19 slava Exp $
 */

// ========================================================================
//  Name        : WBMPImage.java
//  Part of     : 
//  Description : 
//  Version     : 
//
//  Copyright (c) 2000 - 2005 Nokia Corporation.
//  This material, including documentation and any related
//  computer programs, is protected by copyright controlled by
//  Nokia Corporation. All rights are reserved. Copying,
//  including reproducing, storing, adapting or translating, any
//  or all of this material requires the prior written consent of
//  Nokia Corporation. This material also contains confidential
//  information which may not be disclosed to others without the
//  prior written consent of Nokia Corporation.
// ========================================================================


package com.nokia.wtk.util.gui;

/* java io */
import java.io.InputStream;
import java.io.IOException;
import java.io.EOFException;
import java.io.ByteArrayInputStream;

/* java.awt */
import java.awt.Image;
import java.awt.Toolkit;

/* java.awt.image */
import java.awt.image.ColorModel;
import java.awt.image.ImageProducer;
import java.awt.image.IndexColorModel;
import java.awt.image.MemoryImageSource;

/**
 * WBMP Image.
 *
 */
public class WBMPImage {

    private int width;
    private int height;
    private Image image;
    private byte [] bytes;
    private int [] pixels;

    /**
     * Creates <code>WBMPImage</code> from the data
     * @param data the data (hopfully) containing a BMP image
     * @throws IOException  if the I/O error occurs or the stream does not
     *                      appear to contains a valid BMP image
     */
    public WBMPImage(byte [] data) throws IOException {
        this(new ByteArrayInputStream(data));
    }

    /**
     * Reads the WBMP image from the stream
     * @param in the input stream to read
     * @throws IOException
     */
    public WBMPImage(InputStream in) throws IOException {
        byte typeField = readByte(in);
        if (typeField != 0) {
            throw new ImageFormatException("unrecognized image format");
        }
        byte fixHeaderField = readByte(in);
        if ((fixHeaderField & 0xc0) != 0) {
            new ImageFormatException("unsupported file format");
        }

        width = readMultiByte(in);
        height = readMultiByte(in);
        bytes = new byte[((width + 7)/8) * height];
        if (in.read(bytes) < bytes.length) throw new EOFException();
    }

    /**
     * Gets the image width
     * @return the image width
     */
    public int getWidth() {
        return width;
    }

    /**
     * Gets the image height
     * @return the image height
     */
    public int getHeight() {
        return height;
    }

    /**
     * Gets the image pixels
     * @return the image pixels
     */
    public int [] getPixels() {
        if (pixels == null) {
            pixels = new int[width * height];
            for (int y=0; y<height; y++) {
                int off = y * ((width+7)/8);
                for (int x=0; x<width; x++) {
                    if ((bytes[off+x/8] & (1 << (7-(x%8)))) != 0) {
                        pixels[y*width + x] = 1;
                    }
                }
            }
            // no longer need the bytes
            bytes = null;
        }
        return pixels;
    }

    /**
     * Converts WBMP image into an Java {@link Image}
     * @return {@link Image} where white pixels are transparent
     */
    public Image getImage() {
        if (image == null) {
            image = createImage(true);
        }
        return image;
    }

    /**
     * Converts WBMP image into an Java {@link Image}
     *
     * @param transparent <code>true</code> to make white pixels transparent,
     *                    <code>false</code> otherwise
     * @return {@link Image} in the specified format
     */
    public Image createImage(boolean transparent) {
        byte[] palette = {(byte)0, (byte)0xff};
        ColorModel cm;
        if (transparent) {
            cm = new IndexColorModel(1, 2, palette, palette, palette, 1);
        } else {
            cm = new IndexColorModel(1, 2, palette, palette, palette);
        }
        ImageProducer producer;
        producer = new MemoryImageSource(width,height,cm,getPixels(),0,width);
        return Toolkit.getDefaultToolkit().createImage(producer);
    }

    /**
     * Reads one byte from the stream, checking for EOF condition
     * @param in the stream to read
     * @return the byte read from the stream
     * @throws IOException if an I/O error or EOF condition occurs
     */
    private static byte readByte(InputStream in) throws  IOException {
        int next = in.read();
        if (next < 0) {
            throw new EOFException();
        }
        return (byte)next;
    }

    /**
     * Decode a multi-byte integer in the WAP format from the input stream.
     *
     * @param in the input stream to read
     * @return the decoded integer
     * @throws IOException if an I/O error or EOF condition occurs
     * */
    private static int readMultiByte(InputStream in) throws  IOException {
        int retval = 0;
        for(int i=0; i<5; i++) {
            int encodedByte = in.read();
            if (encodedByte < 0) {
                throw new EOFException();
            }
            retval += (int)(encodedByte & 0x7F);
            if ((encodedByte & 0x80) == 0) {
                break;
            }
            retval <<= 7;
        }
        return retval;
    }
}
