import java.util.Date;

public class GNSSPoint {
	public Date timestamp;
	public double latitude;
	public double longitude;
	public GNSSPoint (Date timestamp, double latitude, double longitude) {
		this.timestamp = timestamp;
		this.latitude = latitude;
		this.longitude = longitude;
	}
}
