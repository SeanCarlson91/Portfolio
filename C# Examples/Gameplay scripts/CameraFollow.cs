using UnityEngine;
using System.Collections;

public class CameraFollow : MonoBehaviour {

	public GameObject player;
	public float fieldOfView;

	void Start () {

	}

	void LateUpdate () {
		transform.position = player.transform.position + Vector3.forward * -fieldOfView;
	}
}
