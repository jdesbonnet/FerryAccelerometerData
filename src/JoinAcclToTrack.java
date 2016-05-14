import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.util.ArrayList;
import java.time.Instant;


/**
 * Join accelerometer segments with tracklog to provide location for each segment
 * 
 * 
 * @author Joe Desbonnet
 *
 */
public class JoinAcclToTrack {

	private static List<GNSSPoint> points;
	private static long[] timestamps;

	private static GNSSPoint findNearestPoint(long ts) {
		int index = Arrays.binarySearch(timestamps, ts);
		if (index < 0) {
			index = -index;
		}
		return points.get(index);
	}
	
	private static void readTrackLog (File trackLogFile) throws IOException {

		BufferedReader r = new BufferedReader(new FileReader(trackLogFile));

		points = new ArrayList<>();

		String line;

		while ( (line=r.readLine())!=null) {
			String[] p = line.split(" ");
			Date timestamp = new Date((long)Double.parseDouble(p[0]));
			double latitude = Double.parseDouble(p[1]);
			double longitude = Double.parseDouble(p[2]);
			GNSSPoint point = new GNSSPoint(timestamp, latitude, longitude);			
			points.add(point);
		}
		
		timestamps = new long[points.size()];
		for (int i = 0; i < timestamps.length; i++) {
			timestamps[i] = points.get(i).timestamp.getTime();
		}
	}

	private static void readSegments (File segFile) throws IOException {
		BufferedReader r = new BufferedReader(new FileReader(segFile));
		String line;
		while ( (line=r.readLine())!=null) {
			String[] p = line.split(" ");
			long ts = (long)Double.parseDouble(p[0]);
			GNSSPoint point = findNearestPoint(ts);
			System.out.println (line + " " + point.latitude + " " + point.longitude);
		}
	}
	
	
	public static void main (String[] arg) throws Exception {
		File trackLogFile = new File(arg[0]);
		File segFile = new File(arg[1]);
		readTrackLog(trackLogFile);
		readSegments(segFile);
	}	

}
