import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.ArrayList;
import java.time.Instant;


/**
 * Read Google MyTracks CSV format file output: timestamp latitude longitude
 * 
 * CSV colums:
 * Segment, Point, Latitude (deg), Longitude (deg), Altitude (m), Bearing (deg), Accuracy (m), speed (m/s), Time
 * 
 * @author Joe Desbonnet
 *
 */
public class ReadMyTracksCSV {

	
	public static void readMyTracksCSV(Reader r) throws IOException {
		BufferedReader bf = new BufferedReader(r);
		
		String line;
		
		double prevLatitude = 0, prevLongitude = 0;
		int prevSegmentId = 0;

		List<GNSSPoint> points = new ArrayList<>();
		
		while (  (line = bf.readLine()) != null) {
			String[] p = line.split(",");
			
			if (p.length < 5) {
				continue;
			}
			
			try {
				
				int segmentId = Integer.parseInt(dequote(p[0]));
				String timestamp = dequote(p[8]);
				double latitude = Double.parseDouble(dequote(p[2]));
				double longitude = Double.parseDouble(dequote(p[3]));
				
				Date ts = Date.from( Instant.parse(timestamp));

				
				if (latitude != prevLatitude || longitude != prevLongitude) {
					points.add(new GNSSPoint(ts,latitude,longitude));
					double tsSec = (double)(ts.getTime())/1000.0;	
					System.out.println (String.format("%.3f",tsSec) 
					+ " "  + latitude + " " + longitude);
					prevLatitude = latitude;
					prevLongitude = longitude;
					
				} else {
					//System.err.println ("skipping duplicate point " + latitude + "," + longitude );
				}
				
			} catch (NumberFormatException e) {
				e.printStackTrace();
			}
			
		}

		long[] timestamps = new long[points.size()];
		int i = 0;	
		for (GNSSPoint point : points) {
			timestamps[i++] = point.timestamp.getTime();
		}
		
	}
	
	/**
	 * Remove quotes from CSV value. For example "POINT" -> POINT
	 * @param s
	 * @return
	 */
	private static String dequote (String s) {
		return s.substring(1,s.length()-1);
	}
	
	public static void main (String[] arg) throws Exception {
		readMyTracksCSV(new InputStreamReader(System.in));
	}	

}
